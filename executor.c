#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "_string.h"
#include "builtin.h"
#include "cmd.h"
#include "common.h"
#include "env.h"
#include "utils.h"
#include "executor.h"
#include "parser.h"

/**
 * _get_x_path - retrieves path to executable
 * @shell: shell's context structure
 * @identifier: potential name of an executable
 *
 * Return: Path to executable else NULL
 */
static const char *_get_x_path(shell_t *shell, const char *identifier)
{
	char *pathv = NULL, *token = NULL, *path = NULL, *cwd = NULL;
	struct stat sb;

	assert(environ != NULL);
	if (_is_abs(identifier))
	{
		if (stat(identifier, &sb) == 0)
			return (identifier);
		fprintf(stderr, "%s: %s: No such file or directory.\n", shell->program,
				identifier);
		return (NULL);
	}

	if (_strncmp(identifier, "./", 2) == 0)
	{
		cwd = _getenv("PWD");
		if (cwd == NULL)
			return (NULL);

		cwd = _strdup(cwd);
		path = join_path(cwd, identifier + 2);
		free(cwd);

		if (stat(path, &sb) == 0)
			return (path);

		fprintf(stderr, "%s: %s: file not found\n", shell->program, identifier);
		return (NULL);
	}

	pathv = _strdup(_getenv("PATH"));
	if (pathv == NULL)
	{
		fprintf(stderr, "%s: failed to find PATH variable\n", shell->program);
		return (NULL);
	}

	token = _strtok(pathv, ":");
	for (; token != NULL; token = _strtok(NULL, ":"))
	{
		path = join_path(token, identifier);
		if (stat(path, &sb) == 0)
		{
			free(pathv);
			return (path);
		}
	}
	free(pathv);
	printf("%s: %s: command not found.\n", shell->program, identifier);
	return (NULL);
}

/**
 * run_cmd_line - runs a command line
 * @shell: shell context structure
 * @line: command line
 *
 * Return: states of execution
 */
static int run_cmd_line(shell_t *shell, char **line)
{
	pid_t pid;
	const char *program = NULL;
	builtin_handler_t func =  NULL;
	int status = 0;

	if (isbuiltin(line[0]))
	{
		func = get_builtin_handler(line[0]);
		func(shell, line);
		return (EXEC_OK);
	}

	program = _get_x_path(shell, line[0]);
	if (program)
	{
		pid = fork();
		if (pid == 0) /**child*/
		{
			execve(program, line, environ);
			fprintf(stderr, "%s: %s\n", line[0], strerror(errno));
			return (EXEC_RUNTIME_ERROR);
		} else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) != 0)
				{
					return (EXEC_RUNTIME_ERROR);
				}
			} else
			{
				fprintf(stderr, "%s: Execution error\n", line[0]);
				return (EXEC_RUNTIME_ERROR);
			}
			return (EXEC_OK);
		} else
		{
			perror("fork");
			return (EXEC_RUNTIME_ERROR);
		}
	}
	return (EXEC_RUNTIME_ERROR);
}

/**
 * run_cmds - executes lines in the cmds
 * @shell: shell's context structure
 * @cmds: cmd lines bucket
 *
 * Return: status
 */
static int run_cmds(shell_t *shell, cmds_t *cmds)
{
	size_t i = 0;
	int status = EXEC_OK;
	op_t *op = cmds->ops;
	char **line = NULL, **line1 = NULL, **line2 = NULL;

	while (op != NULL)
	{
		if (op->value == OP_SIMPLE)
		{
			line = cmds->lines[i]->items;
			status = run_cmd_line(shell, line);
		} else if (op->value == OP_BIN_AND)
		{
			line1 = cmds->lines[i]->items;
			line2 = cmds->lines[i + 1]->items;

			status = run_cmd_line(shell, line1);
			if (status == EXEC_OK)
			{
				status = run_cmd_line(shell, line2);
			}
			i++;
		}
		if (status != EXEC_OK)
		{
			break;
		}
		op = op->next;
		i++;
	}
	return (status);
}

/**
 * execute - executes commands lines
 * @shell: shell's context structure
 * @source: input string
 * Return: status
 */
int execute(shell_t *shell, char *source)
{
	int status = EXEC_OK;
	bool parsed = false;

	shell->cmds = malloc(sizeof(cmds_t));
	if (shell->cmds == NULL)
	{
		return (EXEC_PARSE_ERROR);
	}
	init_cmds(shell->cmds);

	parsed = parse(shell->cmds, source);
	free(source);
	if (!parsed)
	{
		free_cmds(&shell->cmds);
		return (EXEC_PARSE_ERROR);
	}

	if (shell->cmds->count < 1)
	{
		free_cmds(&shell->cmds);
		return (EXEC_OK);
	}

	status = run_cmds(shell, shell->cmds);
	free_cmds(&shell->cmds);
	return (status);
}

