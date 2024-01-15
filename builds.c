#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common.h"
#include "env.h"
#include "_string.h"

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
		for (i = 0; i < shell->env.count; i++)
		{
			fprintf(stdout, "%s\n", shell->env.items[i]);
		}
	}
	return (0);
}

/**
 * _setenv - Initializes new environment variable or modifies one
 * @shell: context structure
 * @argv: arguments
 *
 * Return: 0 on success -1 on failure
 */
int _setenv(shell_t *shell, char **argv)
{
	char **entry = NULL, *str = NULL, *val = NULL;
	size_t n_key = 0, n_val = 0;

	if (!argv || !argv[0] || !argv[1])
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}

	entry = get_env_var_addr(&(shell->env), argv[0]);
	n_key = _strlen(argv[0]);
	n_val = _strlen(argv[1]);

	str = malloc(n_key + n_val + 2);
	if (str == NULL)
	{
		fprintf(stderr, "Failed to allocate env var.\n");
		return (1);
	}

	_strncpy(str, argv[0], n_key);
	_strncat(str, "=", 1);
	_strncat(str, argv[1], n_val);

	if (entry != NULL)
	{
		val = _strchr(*entry, '=');
		if (_strcmp((++val), argv[1]) != 0)
		{
			free(*entry);
			*entry = str;
		} else
		{
			free(str);
		}
	} else
	{
		add_env_var(&(shell->env), str);
	}
	return (0);
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
	char **entry = NULL, *val = NULL, *str = NULL;
	size_t n_key = 0;

	if (!argv || !argv[0])
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}

	entry = get_env_var_addr(&shell->env, argv[0]);
	if (entry != NULL)
	{
		n_key = _strlen(argv[0]);
		val = _strchr(*entry, '=');
		if (val && *(val + 1))
		{
			str = malloc(n_key + 1);
			if (str == NULL)
			{
				perror("malloc");
				return (1);
			}

			_strncpy(str, argv[0], n_key);
			_strncat(str, "=", 1);

			free(*entry);
			*entry = str;
		}
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
		home_dir = get_env(&shell->env, "HOME");
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
			old_pwd = get_env(&shell->env, "OLDPWD");
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

