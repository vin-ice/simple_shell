#include <assert.h>
#include <stdio.h>
#include <sys/types.h>

#include "env.h"
#include "mem.h"
#include "_string.h"

/**
 * init_env - initializes the environment variable bucket
 * @envs: environment variables' structure
 * @envp: environment variable pointer
 *
 * Return: true on completion else false
 */
bool init_env(envs_t **envs, char **envp)
{
	size_t i = 0;
	static envs_t env;

	if (!envp || !*envp)
	{
		return (false);
	}

	env.items = NULL;
	env.count = 0;
	env.capacity = 0;

	for (i = 0; envp[i]; i++)
	{
		if (!add_env_var(&env, envp[i]))
		{
			return (false);
		}
	}
	env.items[i] = NULL;
	*envs = &env;
	return (true);
}

/**
 * free_env - frees environment variables
 * @envs: env bucket
 */
void free_env(envs_t *envs)
{
	size_t i = 0;

	if (envs && envs->items)
	{
		for (i = 0; i < envs->count; i++)
		{
			free(envs->items[i]);
		}
		FREE_ARRAY(char *, envs->items, envs->capacity);
	}
}

/**
 * get_env_var_addr - finds a shell variable and
 *	returns its address in the envs
 * @envs: shell's environment variable's bucket
 * @name: name of shell variable
 *
 * Return: address of shell variable if found else NULL
 */
char **get_env_var_addr(envs_t *envs, char *name)
{
	size_t i = 0;
	char *key = NULL, *cpy = NULL;
	size_t n_key = 0;

	if (envs == NULL || (envs->items == NULL || envs->count == 0))
	{
		return (NULL);
	}

	for (i = 0; i < envs->count; i++)
	{
		cpy = _strdup(envs->items[i]);
		key = _strtok(cpy, "=");
		n_key = _strlen(key);
		if (_strncmp(key, name, n_key) == 0)
		{
			free(cpy);
			return (&(envs->items[i]));
		}
		free(cpy);
	}
	return (NULL);
}

/**
 * get_env - retrives value of an env variable
 * @envs: environment variables' bucket
 * @name: env identifier;
 *
 * Return: value of env variable else NULL
 */
char *get_env(envs_t *envs, char *name)
{
	char **entry = NULL;

	entry = get_env_var_addr(envs, name);
	if (entry != NULL && *entry != NULL)
	{
		return (_strchr(*entry, '=') + 1);
	}

	return (NULL);
}

/**
 * add_env_var - adds variable into the env variable bucket
 * @envs: env variable bucket
 * @val: variable/value
 *
 * Return: return true or false
 */
bool add_env_var(envs_t *envs, char *val)
{
	size_t old_capacity = 0;

	if (envs->capacity < envs->count + 2)
	{
		old_capacity = envs->capacity;
		envs->capacity = GROW_CAPACITY(old_capacity);
		envs->items = GROW_ARRAY(char *, envs->items,
								old_capacity, envs->capacity);

		if (envs->items == NULL)
		{
			fprintf(stderr, "add_env_var: Failed to load shell variables\n");
			return (false);
		}
	}

	envs->items[envs->count] = _strdup(val);
	envs->count++;
	return (true);
}

