#include "shell.h"
/**
 * _getenv - searched for specified environment variable
 * @var_name: specified envt variable name
 * Return: returns pointer to variable values or NULL
 */

char *_getenv(char *var_name)
{   
    char *var_vals = NULL;
    int n, count, len;

    n = strlen(var_name);
    for (count = 0; environ[count] != NULL; count++)
    {
        if (strncmp(environ[count], var_name, n) == 0)
        {
            len = strlen(environ[count]);
            var_vals = malloc(sizeof(char) * len + 1);
            if (var_vals == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strncpy(var_vals, (environ[count] + n + 1), len);
            return (var_vals);
        }
    }
    return (NULL);
}