#include "shell.h"
/**
 * strip_line - strips non-character line from
 * end of line
 * @str: string
 * @n: size of str
 * 
 * Return: string
 */
void parse_line(char *str, ssize_t n)
{
    if (str[n - 1] == '\n')
        str[n - 1] = '\0';
}
/**
 * isexe - looks for executable for given argument
 * @str: path
 * Return: 1 if true else 0
 */
