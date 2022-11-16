#include "shell.h"
char *_strtok_r(char *str, const char *delim, char **last);
/**
 * _strtok - returns _strtok_r
 * zero or more nonempty tokens
 * @str: source string
 * @delim: String of a collection of delimiters
 * Return: pointer to next token or null
 */
char *_strtok(char *str, const char *delim)
{
    static char *last;
    
    return (_strtok_r(str, delim, &last)); 
}
/**
 * _strtok - breaks a string into a sequence of
 * zero or more nonempty tokens
 * @str: source string
 * @delim: String of a collection of delimiters
 * Return: pointer to next token or null
 */
char *_strtok_r(char *str, const char *delim, char **last)
{
    char *token;

    if (str == NULL)
        str = *last;
    /* Scan leading delimiters.  */
    str += strspn(str, delim);
    if (*str == '\0')
        return NULL;
    /* Find the end of the token.  */
    token = str;
    str = strpbrk(token, delim);
    if (str == NULL)
        /* This token finishes the string.  */
        *last = strchr(token, '\0');
    else {
        /* Terminate the token and make *SAVE_PTR point past it.  */
        *str = '\0';
        *last = str + 1;
    }
    return (token);
}