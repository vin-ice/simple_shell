#include <stdlib.h>

#include "_string.h"

/**
 * _strtok - returns _strtok_r
 * zero or more nonempty tokens
 * @str: source string
 * @sep: String of a collection of delimiters
 * Return: pointer to next token or null
 */
char *_strtok(char *str, const char *sep)
{
	static char *last;

	if (last == NULL && str == NULL)
	{
		return (NULL);
	} else if (last == NULL)
	{
		last = str;
	}

	return (_strtok_r(str, sep, &last));
}

/**
 * _strlen - returns the length of a string
 * @s: points to location of a string variable
 * Return: returns length of variable *s
 */
size_t _strlen(const char *s)
{
	size_t len = 0;

	while (s[len] != '\0')
		len++;
	return (len);
}

/**
 * _strnlen - returns number of bytes by string pointed by s upto a max of n
 * @s: string pointer
 * @n: maximum bytes to consider
 *
 * Return: length
 */
size_t _strnlen(const char *s, size_t n)
{
	size_t len = 0;

	for (len = 0; len < n; len++)
	{
		if (s[len] == '\0')
		{
			return (len);
		}
	}
	return (len);
}

/**
 * _strstr - locates a substring
 * @haystack: string in which to check for needle
 * @needle: substring to find in haystack
 *
 * Return: pointer to beginning of needle in haystack or NULL if no match
 */
char *_strstr(char *haystack, char *needle)
{
	unsigned int i = 0, j = 0;

	while (haystack[i])
	{
		while (needle[j] && (haystack[i] == needle[0]))
		{
			if (haystack[i + j] == needle[j])
				j++;
			else
				break;
		}
		if (needle[j])
		{
			i++;
			j = 0;
		}
		else
			return (haystack + i);
	}
	return (0);
}

/**
 * _strdup - duplicate a string
 * @s: string to duplicate
 * Return: returns pointer to the memory of new string
 */
char *_strdup(const char *s)
{
	char *str = NULL;
	size_t len = 0, count = 0;

	if (s == NULL)
	{
		return (NULL);
	}

	len = _strlen(s);

	if (len < 1)
	{
		return (NULL);
	}

	str = (char *) malloc(sizeof(char) * (len + 1));
	if (str == NULL)
	{
		return (NULL);
	}

	for (count = 0; count <= len; count++)
	{
		str[count] = s[count];
	}

	str[len] = '\0';
	return (str);
}

