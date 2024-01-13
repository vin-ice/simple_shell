#include <stdlib.h>

#include "_string.h"

/**
 * _strndup - copies n bytes of string pointed to by s to a new location
 * @s: string pointer
 * @n: max bytes to copy
 *
 * Return: returns copy of s
 */
char *_strndup(const char *s, size_t n)
{
	size_t count = 0, len = 0;
	char *str = NULL;

	if (s && n > 0)
	{
		while (len < n && s[len])
		{
			len++;
		}
		if (len < 1)
		{
			return (NULL);
		}

		str = malloc(sizeof(char) * (len + 1));
		if (str == NULL)
		{
			return (NULL);
		}

		while (count <= len)
		{
			str[count] = s[count];
			count++;
		}
		str[len] = '\0';
	}

	return (str);
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: 0 if same else difference of characters
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strncmp - compares two string upto n bytes
 * @s1: string 1
 * @s2: string 2
 * @n : size of bytes to compare
 *
 * Return: 0 if same else difference of characters
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
		--n;
	}

	if (n == 0 || (*s1 == '\0' && *s2 == '\0'))
	{
	    return (0);
	} else
	{
		return (*s1 - *s2);
    }
}

/**
 * _strchr - locates a character in a string
 * @s: string to check
 * @c: character to check for
 *
 * Return: pointer to spot in s with c or null
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
		{
			return ((char *) s);
		}
		s++;
	}

	return (NULL);
}

