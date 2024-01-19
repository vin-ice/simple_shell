#include <stdio.h>
#include <stdarg.h>

#include "utils.h"
#include "mem.h"

/**
 * _is_word - checks if character is word-like
 * @c: character
 * Return: true or false
 */
bool _is_word(const char c)
{
	return (_is_alpha(c) || _is_digit(c) || c == '_' ||
			c == '~' || c == '.' || c == '/' || c == '?' || c == '-');
}

/**
 * _is_name - checks if character consists only of alphanumerics and underscore
 * @c: character
 * Return: true else false
 */
bool _is_name(char c)
{
	return (_is_alpha(c) || _is_digit(c) || c == '_');
}

/**
 * _is_control_operator - checks if character is a control operator
 * @c: character
 * Return: true else false
 */
bool _is_control_operator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '\n');
}

/**
 * mk_string - creates and populates a null-terminated string
 * @size: size of string
 * Return: new string
 */
char *mk_string(size_t size, ...)
{
	va_list ap;
	char *str = NULL, *arg = NULL;
	size_t len = 0, n_arg = 0;

	str = ALLOCATE(char, (size + 1));
	if (str == NULL)
	{
		perror("mk_str: malloc");
		return (NULL);
	}

	va_start(ap, size);
	while ((arg = va_arg(ap, char *)) != NULL)
	{
		n_arg = _strlen(arg);
		if (len + n_arg <= size)
		{
			_strcat(str, arg);
			len += n_arg;
		} else
		{
			break;
		}
	}
	va_end(ap);
	str[len + 1] = '\0';
	return (str);
}

