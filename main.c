#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <libgen.h>

#include "common.h"
#include "input.h"
#include "parser.h"
#include "executor.h"
#include "_string.h"
#include "mem.h"
#include "env.h"

/**
 * init_shell - Initializes shell context
 * @shell: shell context structure
 * @name: program's name
 * @envp: environment variables
 *
 * Return: true if complete else false
 */
static bool init_shell(shell_t *shell, char *name, char **envp)
{
	shell->program = basename(name);
	shell->cmds = NULL;
	shell->envs = NULL;

	if (!envp || !*envp)
	{
		return (false);
	}

	return (init_env(&shell->envs, envp));
}

/**
 * free_shell - destroys shell
 * @shell: context structure
 */
void free_shell(shell_t *shell)
{
	if (shell != NULL)
	{
		free_env(shell->envs);
		free_cmds((cmds_t *) shell->cmds);
	}
}

/**
 * repl - read, evaluate, print loop
 * @shell: shell's context structure
 * TODO: implement the Ctrl+D handler to exit the loop
 */
static void repl(shell_t *shell)
{
	ssize_t n_read = 0;
	char *input = NULL;
	size_t n = 0;

	for (;;)
	{
		fprintf(stdout, "%s> ", shell->program);
		fflush(stdout);

		n_read = _getline(&input, &n, stdin);
		if (n_read > 0)
		{
			execute(shell, input);
		} else if (n_read < 0)
		{
			fprintf(stderr, "%s: %s\n",
					shell->program, strerror(errno));
		} else
		{
			fprintf(stdout, "\n");
		}
		input = NULL, n = 0;
	}

}

/**
 * main - Driver function for the shell and executes programs
 * @argc: argument count
 * @argv: arguments' vector
 * @envp: environment variables
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **envp)
{
	static shell_t shell;
	char *input = NULL;
	ssize_t n_read = 0;
	size_t n = 0;

	if (!init_shell(&shell, argv[0], envp))
	{
		fprintf(stderr, "%s: init_shell: Failed to initialize shell\n",
				argv[0]);
		return (1);
	}

	if (argc > 1)
	{
		input = read_file(argv[1]);
		if (input != NULL)
		{
			execute(&shell, input);
		}
	} else
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			repl(&shell);
		} else
		{
			while (true)
			{
				n_read = _getline(&input, &n, stdin);
				if (n_read > 0)
				{
					execute(&shell, input);
				} else
				{
					break;
				}
				input = NULL, n = 0;
			}
		}
	}
	return (0);
}

