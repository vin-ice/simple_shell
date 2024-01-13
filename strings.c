#include <stdlib.h>

#include "_string.h"

/**
 * _strcat - concatenates two string
 * @dest: first string
 * @src: second string
 *
 * Return: Pointer to string
 */
char *_strcat(char *dest, const char *src)
{
	char *start = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = '\0';
	return (start);
}

/**
 * _strncat - concatenates n-size string to destination
 * @dest: Destination string to append to
 * @src: String to append to dest
 * @n: size of src string to append
 * Return: returns string
 */
char *_strncat(char *dest, const char *src, int n)
{
	int i;
	char *start = dest;

	while (*dest)
		dest++;

	for (i = 0; *src && i < n; i++)
		*dest++ = *src++;

	*dest = '\0';
	return (start);
}

/**
 * _strcpy - copies string to a location
 * @dest: destination location
 * @src: source location/string
 *
 * Return: new location
 */
char *_strcpy(char *dest, const char *src)
{
	char *start = dest;

	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (start);
}

/**
 * _strncpy - copies a string to a location
 * @dest: Destination location to copy string to
 * @src: Source string
 * @n: size of string to copy
 * Return: returns destination address
 */
char *_strncpy(char *dest, const char *src, int n)
{
	char *start = dest;
	int i = 0;

	for (i = 0; i < n; i++)
	{
		if (*src)
			*dest++ = *src++;
		else
			*dest++ = '\0';
	}
	return (start);
}

/**
 * _strtok_r - segmements string on encountering any
 *	character specified in the delim
 * @str: string to break
 * @sep: string of deliminating characters
 * @saveptr: pointer to saved line
 *
 * Return: string else NULL
 */
char *_strtok_r(char *str, const char *sep, char **saveptr)
{
	char *token = NULL;

	if (str == NULL)
	{
		str = *saveptr;
	}

	while (*str != '\0' && _strchr(sep, *str) != NULL)
	{
		str++;
	}

	if (*str == '\0')
	{
		return (NULL);
	}

	token = str;

	while (*str != '\0' && _strchr(sep, *str) == NULL)
	{
		str++;
	}

	if (*str != '\0')
	{
		*str++ = '\0';
	}

	*saveptr = str;

	return (token);
}

