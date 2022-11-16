#include "shell.h"
int count = 0;
void _execute(cmd_t *cmd);
/**
 * exec - executes a command and constituent options and args
 * @cmd: command line
 * Return: void
 */ 
int execute(cmd_t *cmd)
{
    alias_t aliases[] = 
    {
        {"ls", "ls"},
        {NULL, NULL}
    };
    builtins_t sh_builtins[] =
    {
        {"exit", __exit},
        {"env", _env},
        {"setenv", _setenv},
        {NULL, NULL}
    };
    
    /*1. aliases*/
    for (count = 0; aliases[count].alias_name != NULL; count++)
    {
        if (_strcmp(cmd->cmd, aliases[count].alias_name) == 0)
            cmd->cmd = aliases[count].real_name;/**change command to full command*/
    }
    /*2. builtins*/
    for (count = 0; sh_builtins[count].name != NULL; count++)
    {
        if (_strcmp(cmd->cmd, sh_builtins[count].name) == 0)/*builtin*/
        {   
            if (sh_builtins[count].f(cmd))
                return (0);
            else
                return (1);
        }
    }
    /*3. env */
    if (!isexec(cmd))
    {
        err_msg("%s: File not found\n", cmd->p_name);
        return (0);
    }
    _execute(cmd);
    return (0);
}
/**
 * isexec -  checks file's status and updates cmd if path found
 * @cmd: Command/path extered
 * Return: 1 if found else 0
 */
int isexec(cmd_t *cmd)
{
    char *paths = NULL, *path = NULL, *token;
    struct stat st;

    if (_strchr(cmd->cmd, '/') == NULL)/*cmd*/
    {   
        paths = _getenv("PATH");
        token = strtok(paths, ":");
        for (; token != NULL; )/*search through paths*/
        {
            path = _strcat(token, "/");
            path = _strcat(path, cmd->cmd);
            if (stat(path, &st) == 0)
            {
                cmd->cmd = path;
                free(paths);
                return (1);
            }
            token = strtok(NULL, ":");
        }
        free(paths);
    }
    else
        if (stat(cmd->cmd, &st) == 0)
            return (1);
    return (0);
}

/**
 * _execute - performance execution
 * @str: alias to find
 * Return: exec path or void
 */
void _execute(cmd_t *cmd)
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