#include <assert.h>
#include <stdio.h>
#include <sys/types.h>

#include "mem.h"
#include "_string.h"
#include "common.h"

/**
 * get_env_var_addr - finds an env variable and returns its address in env arr
 * @name: variable name
 * Return: returns env address
 */
char **get_env_var_addr(char *name)
{
	size_t i = 0;
	char **addr = NULL, *key = NULL, *cpy = NULL;

	if (name == NULL)
	{
		return (NULL);
	}

	assert(environ != NULL);
	for (i = 0; environ[i] != NULL; i++)
	{
		cpy = _strdup(environ[i]);
		key = _strtok(cpy, "=");
		if (_strcmp(key, name) == 0)
		{
			free(cpy);
			addr = &environ[i];
			break;
		}
		free(cpy);
	}
	return (addr);
}

/**
 * _getenv - returns pointer to value of the env variable
 * @name: name of variable
 * Return: value else NULL
 */
char *_getenv(char *name)
{
	char **env_addr;

	if (name != NULL)
	{
		env_addr = get_env_var_addr(name);
		if (env_addr != NULL && *env_addr != NULL)
		{
			return (_strchr(*env_addr, '=') + 1);
		}
	}
	return (NULL);
}

