#include "shell.h"
/**
 * _strlen - returns the length of a string
 * @s: points to location of a string variable
 * Return: returns length of variable *s
 */
int _strlen(char *s)
{
	int counter = 0;

	while (*(s + counter) != '\0')
		counter++;
	return (counter);
}
/**
 * _strcat - concatenates two string
 * @str1: first string
 * @str2: second string
 * 
 * Return: Pointer to string
 */
char *_strcat(char *str1, char *str2)
{
	int len;
	char *str;

	len = strlen(str1) + strlen(str2);
	str = malloc(sizeof (char) * len + 1);
	if (str == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	_strncpy(str, str1, strlen(str1));
    strcat(str, str2);
	return (str);
}
/**
* _strncat - concatenates n-size string to destination
* @dest: Destination string to append to
* @src: String to append to dest
* @n: size of src string to append
* Return: returns string
*/
char *_strncat(char *dest, char *src, int n)
{
	int length, j;
	
	length = 0;
	while (dest[length] != '\0')
	{
		length++;
	}
	for (j = 0; j < n && src[j] != '\0'; j++, length++)
	{
		dest[length] = src[j];
	}
	dest[length] = '\0';
	return (dest);
}
/**
 * _strncpy - copies a string to a location
 * @dest: Destination location to copy string to
 * @src: Source string
 * @n: size of string to copy
 * Return: returns destination address
 */
char *_strncpy(char *dest, char *src, int n)
{
	int byteCount;
	for (byteCount = 0; byteCount < n && src[byteCount] != '\0'; byteCount++)
		dest[byteCount] = src[byteCount];
	for (; byteCount < n; byteCount++)
		dest[byteCount] = '\0';
	return (dest);
}
/**
 * _strcmp - compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: returns 
 */
int _strcmp(char *s1, char *s2)
{
	int counter, cmpVal;

	counter = 0;
	while (s1[counter] == s2[counter] && s1[counter] != '\0')
	{
		counter++;
	}

	cmpVal = s1[counter] - s2[counter];
	return (cmpVal);
}
/**
 * _strncmp - compares first n characters of strings
 * @str1: first string
 * @str2: second string
 * n: len to differentiate
 * 
 * Return: returns difference
 */
int _strncmp(char *s1, char *s2, int n)
{
	int count, cmpVal;

	for (count = 0; count < n && s1[count] == s2[count] && s1[count] != '\0'; count++)
		if (count == n -1)
			return (s1[count] - s2[count]);
	cmpVal = s1[count] - s2[count];
	return (cmpVal);
}
/**
 * _strchr - locates a character in a string
 * @s: string to check
 * @c: character to check for
 *
 * Return: pointer to spot in s with c or null
 */
char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; *(s + i); i++)
	{
		if (*(s + i) == c)
			return (s + i);
	}
	if (*(s + i) == c)
		return (s + i);
	return (NULL);
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