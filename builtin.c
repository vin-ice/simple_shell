#include <stdlib.h>
#include <stdio.h>

#include "builtin.h"
#include "common.h"
#include "_string.h"

const builtin_t builds[] = {
	{"exit", __exit},
	{"env", _env},
	{"setenv", _setenv},
	{"unsetenv", _unsetenv},
	{"cd", _cd},
	{NULL, NULL},
};

/**
 * isbuiltin - checks if identifier matches any builtin program
 * @id: varchar identifying a build
 * Return: true if present else false
 */
bool isbuiltin(char *id)
{
	int i = 0;

	while (builds[i].identifier != NULL)
	{
		if (_strcmp(builds[i].identifier, id) == 0)
			return (true);
		i++;
	}
	return (false);
}

/**
 * get_builtin_handler - returns handler function for builtin
 * @id: identifier of the builtin
 *
 * Return: pointer to function else NULL
 */
builtin_handler_t get_builtin_handler(char *id)
{
	int i = 0;

	while (builds[i].identifier != NULL)
	{
		if (_strcmp(builds[i].identifier, id) == 0)
			return (builds[i].handler);
		i++;
	}
	return (NULL);
}

