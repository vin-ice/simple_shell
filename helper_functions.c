#include "shell.h"
int BUF_SIZE = 120;
/**
 * strip_line - strips non-character line from
 * end of line
 * @str: string
 * @n: size of str
 * 
 * Return: string
 */
void strip_line(char *str, ssize_t n)
{
    if (str[n - 1] == '\n')
        str[n - 1] = '\0';
}