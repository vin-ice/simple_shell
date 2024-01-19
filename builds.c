#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common.h"
#include "_string.h"
#include "mem.h"
#include "executor.h"
#include "env.h"

/**
 * __exit - custom exit method
 * @shell: context
 * @argv: argument vector
 *
 * Return: status
 */
int __exit(shell_t *shell, char **argv)
{
	int status = 0;

	if (argv && argv[1])
	{
		status = atoi(argv[1]);

		if (status < 0)
		{
			fprintf(stderr, "exit expects an integer status\n");
			return (1);
		}
	}

	free_shell(shell);
	exit(status);
}

/**
 * _env - prints current environment
 * @shell: shell's context structure
 * @argv: arguments
 *
 * Return: 0 on success -1 on fail
 */
int _env(shell_t *shell, char **argv)
{
	size_t i = 0;

	(void) argv;
	if (shell != NULL)
	{
		for (i = 0; environ[i]  != NULL; i++)
		{
			fprintf(stdout, "%s\n", environ[i]);
		}
	}
	return (0);
}

/**
 * _setenv - Initializes new environment variable or modifies an existing one
 * @shell: context structure
 * @argv: arguments
 *
 * Return: 0 on success -1 on failure
 */
int _setenv(shell_t *shell, char **argv)
{
	char **ent_addr = NULL, *str = NULL, *val = NULL, *cpy = NULL;
	size_t n_key = 0, n_val = 0, i = 0;

	(void) shell;
	if (!argv || !argv[0] || !argv[1])
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}

	n_key = _strlen(argv[0]);
	n_val = _strlen(argv[1]);

	ent_addr = get_env_var_addr(argv[0]);
	if (ent_addr != NULL && *ent_addr != NULL)
	{
		cpy = _strdup(*ent_addr);
		_strtok(cpy, "=");
		val = _strtok(NULL, " \n\t");
		if (_strcmp(val, argv[1]) != 0)
		{
			str = mk_string((n_key + n_val + 1), argv[0], "=", argv[1]);
			if (str == NULL)
			{
				free(cpy);
				return (EXEC_RUNTIME_ERROR);
			}
			free(*ent_addr);
			*ent_addr = str;
		}
		free(cpy);
	} else
	{
		environ = GROW_ARRAY(char *, environ, i, i + 1);
		if (environ == NULL)
			exit(EXEC_RUNTIME_ERROR);

		str = mk_string((n_key + n_val + 2), argv[0], "=", argv[1]);
		if (str == NULL)
			return (EXEC_RUNTIME_ERROR);
		environ[i] = str;
		environ[i + 1] = NULL;
	}
	return (EXEC_OK);
}

/**
 * _unsetenv - removes an env variable
 * @shell: context structure
 * @argv: argument vector
 *
 * Return: 0 on success -1 on failure
 */
int _unsetenv(shell_t *shell, char **argv)
{
	char *entry = NULL, *key = NULL, *val = NULL, *str = NULL, *cpy = NULL;
	size_t n_key = 0, i = 0;

	(void) shell;
	if (!argv || !argv[0])
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}

	n_key = _strlen(argv[0]);
	assert(environ != NULL);
	for (i = 0; environ[i] != NULL; i++)
	{
		cpy = _strdup(environ[i]);
		key = _strtok(cpy, "=");
		if (key && _strcmp(key, argv[0]) == 0)
		{
			free(cpy);
			entry = environ[i];
			break;
		}
		free(cpy);
	}

	if (entry)
	{
		cpy = _strdup(entry);
		key = _strtok(cpy, "=");
		val = _strtok(NULL, " \t\r\n");
		if (val)
		{
			str = mk_string((n_key + 1), argv[0], "=");
			if (str == NULL)
			{
				free(cpy);
				perror("unsetenv: malloc");
				return (EXEC_RUNTIME_ERROR);
			}
			free(environ[i]);
			environ[i] = str;
		}
		free(cpy);
	}
	return (0);
}

/**
 * _cd - changes the current directory of the process
 * @shell: context structure
 * @argv: arguments vector
 *
 * Return: 0 on success -1 on failure
 */
int _cd(shell_t *shell, char **argv)
{
	static char *args[2] = {"PWD", NULL};
	char *home_dir = NULL, *old_pwd = NULL;

	if (argv && !*argv)
	{
		home_dir = _getenv("HOME");
		if (!home_dir)
		{
			fprintf(stderr, "%s: cd: HOME not set.\n", shell->program);
			return (1);
		}

		old_pwd = getcwd(NULL, 0);
		if (chdir(home_dir) != 0)
		{
			perror("chdir");
			return (1);
		}

		args[1] = getcwd(NULL, 0);
		_setenv(shell, args);

		if (old_pwd)
		{
			args[1] = old_pwd;
			_setenv(shell, args);
			free(old_pwd);
		}
	} else if (argv && *argv)
	{
		if (*argv[0] == '-')
		{
			old_pwd = _getenv("OLDPWD");
			if (!old_pwd)
			{
				fprintf(stderr, "%s: cd: OLDPWD not set\n",
						shell->program);
				return (1);
			}

			if (chdir(old_pwd) != 0)
			{
				perror("chdir");
				return (1);
			}

			args[1] = getcwd(NULL, 0);
			_setenv(shell, args);
		} else
		{
			old_pwd = getcwd(NULL, 0);
			if (chdir(argv[0]) != 0)
			{
				perror("chdir");
				return (1);
			}

			args[1] = getcwd(NULL, 0);
			_setenv(shell, args);

			if (old_pwd)
			{
				args[1] = old_pwd;
				_setenv(shell, args);
				free(old_pwd);
			}
		}
	}
	return (0);
}

