#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "_string.h"
#include <string.h>


/**
 * _is_alpha - checks if character is an alphabet
 * @c: character
 * Return: true if alphabet else false
 */
bool _is_alpha(const char c)
{
	return ((c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z') ||
			c == '_');
}

/**
 * _is_digit - checks if character is a digit
 * @c: character
 * Return: true else false
 */
bool _is_digit(const char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * _is_abs - checks if string is absolute path like
 * @input: string to check
 * Return: true if it begins with '/' else false
 */
bool _is_abs(const char *input)
{
	if (input && _strncmp(input, "/", 1) == 0)
		return (true);
	return (false);
}

/**
 * join_path - joins two paths with a '/' character
 * @base: base of path
 * @part: part to append to base
 *
 * Return: memory to new path string
 * if any component is an abs path, prev path are discarded
 * TODO
 * correctly store new path
 */
char *join_path(const char *base, const char *part)
{
	static char path[PATH_MAX] = {0};
	size_t n_base = 0, n_part = 0;

	memset(path, '\0', PATH_MAX);

	if (_is_abs(part))
	{
		_strncat(path, part, PATH_MAX - 1);
		return (path);
	}

	n_base = _strlen(base);
	n_part = _strlen(part);

	if (n_base > 0)
	{
		_strncat(path, base, PATH_MAX - 1);
		_strncat(path, "/", PATH_MAX - _strlen(path) - 1);
	}

	if (n_part > 0)
	{
		if (path[n_base - 1] !=  '/')
		{
			path[n_base] = '/';
			path[n_base + 1] = '\0';
		}
		_strncat(path, part, PATH_MAX - _strlen(path) - 1);
	}

	return (path);
}

