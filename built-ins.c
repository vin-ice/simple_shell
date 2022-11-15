#include "shell.h"
void _execute_c(cmd_t *cmd);
int __exit( cmd_t *cmd)
{
    int status = 1; 

    printf("====built-ins.c->__exit====\n");
    if (cmd->args[0])
    {
        exit (status);
    }
    exit (1);
}
/**
 * prints the environment variables to
 *  the stdout
 */
int _env(__attribute__((unused)) cmd_t *cmd)
{
    int count;
    char *paths = NULL;

    printf("====built-ins.c->_env====\n");
    for (count = 0; (paths = environ[count]) != NULL; count++)
        printf("%s\n", paths);
    return (1);
}
int _setenv(cmd_t *cmd)
{   
    printf("=====built-ins.c->_setenv====\n");
    if (!cmd->args[1] || cmd->args[1] == NULL)
    {
        err_msg("%s: %s: Usage <variable>\n", NAME, cmd->cmd);
        return (0);
    }
    if (!cmd->args[2] || cmd->args[2] == NULL)
    {
        err_msg("%s: %s: Usage <variable VALUE>\n", NAME, cmd->cmd);
        return (0);
    }
    if (setenv(cmd->args[1], cmd->args[2], 1) == -1)
    {
        perror("setenv");
        return (0);
    }
    return (1);
}
int _unsetenv(cmd_t *cmd)
{   
    printf("=====built-ins.c->_setenv====\n");
    if (!cmd->args[1] || cmd->args[1] == NULL)
    {
        err_msg("%s: %s: Usage <variable>\n", NAME, cmd->cmd);
        return (0);
    }
    if (unsetenv(cmd->args[1], cmd->args[2], 1) == -1)
    {
        perror("unsetenv");
        return (0);
    }
    return (1);
}
/**
 * _execute - performance execution
 * @str: alias to find
 * Return: exec path or void
 */
void _execute_c(cmd_t *cmd)
{
    switch (fork())
    {
        case -1:
            perror("fork");
            break;
        case 0:/*child scope*/
            if (execve(cmd->cmd, cmd->args, environ) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            sleep(2);
            break;
    }
}