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
 *
 * Return: true if complete else false
 */
static void init_shell(shell_t *shell, char *name)
{
	shell->program = name;
	shell->cmds = NULL;
}

/**
 * free_shell - destroys shell
 * @shell: context structure
 */
void free_shell(shell_t *shell)
{
	if (shell != NULL)
	{
		free_cmds(&shell->cmds);
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
	char **environ = envp;
	int status = 0;

	(void) environ;
	init_shell(&shell, argv[0]);

	if (argc > 1)
	{
		input = read_file(argv[1]);
		if (input != NULL)
		{
			status = execute(&shell, input);
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
					status = execute(&shell, input);
				} else
				{
					break;
				}
				input = NULL, n = 0;
			}
		}
	}
	free_shell(&shell);
	return (status);
}

