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
/**
 * parse_line - breaks string into tokens and loads to dest
 * @dest: holds tokens
 * @str: original string
 * @delim: delimiter
 * 
 * Return: void
 */
char **parse_cmd(char *src)
{
    int len = BUF_SIZE;/*3*/
    int count = 0;
    char *delim = " ";
    char *token = NULL, **dest;

    /*init dest*/
    dest = malloc(sizeof (char *) * len);
    if (dest == NULL)
        err_exit("Memory not allocated");
    token = strtok(src, delim);
    while (token != NULL)
    {
        dest[count] = token;
        if (count >= len)
        {
            len += BUF_SIZE;
            dest = realloc(dest, len * sizeof (char *));

        }
        token = strtok(NULL, delim);
        count++;
    }
    dest[count] = NULL;
    return (dest);
}