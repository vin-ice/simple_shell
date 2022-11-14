#include "shell.h"
int count = 0;
void _execute(char *path, char **cmd_line);
/**
 * exec - executes a command and constituent options and args
 * @cmd_line: command line
 * Return: void
 */ 
int execute(char **cmd_line)
{
    alias_t aliases[] = 
    {
        {"ls", "ls"},
        {NULL, NULL}
    };
    builtins_t sh_builtins[] =
    {
        {}
        {NULL, NULL}
    };
    
    printf("\n==== shell-core.c->execute====\n");
    /*1. aliases*/
    for (count = 0; aliases[count].alias_name != NULL; count++)
    {
        if (_strcmp(cmd_line[0], aliases[count].alias_name) == 0)
            cmd_line[0] = aliases[count].real_name;/**change command to full command*/
    }
    printf("%s\n", cmd_line[0]);
    /*2. builtins*/
    for (count = 0; sh_builtins[count].name != NULL; count++)
    {
        if (_strcmp(cmd_line[0], aliases[count].alias_name) == 0)
        {
            /*sh_builtins[count].f;*/
            printf("Found builtin function");
            return (1);
        }
    }
    printf("%s\n", cmd_line[0]);
    /*3. env */
    if (!isexec(&(cmd_line[0])))
    {
        err_msg("%s: File not found", NAME);
        return (0);
    }
    _execute(cmd_line[0], cmd_line);
    return (0);
}
/**
 * isexec -  checks file's status and updates cmd if path found
 * @cmd: Command/path extered
 * Return: 1 if found else 0
 */
int isexec(char **cmd)
{
    char *paths = NULL, *path = NULL, *token;
    struct stat st;

    printf("\n==== shell-core.c->isexec====\n");

    if (_strchr(*cmd, '/') == NULL)/*cmd*/
    {   
        paths = _getenv("PATH");
        token = strtok(paths, ":");
        for (; token != NULL; )/*search through paths*/
        {
            path = _strcat(token, "/");
            path = _strcat(path, *cmd);
            if (stat(path, &st) == 0)
            {
                *cmd = path;
                free(paths);
                return (1);
            }
            token = strtok(NULL, ":");
        }
        free(paths);
    }
    else
        if (stat(*cmd, &st) == 0)
            return (1);
    return (0);
}

/**
 * _execute - performance execution
 * @str: alias to find
 * Return: exec path or void
 */
void _execute(char *path, char **cmd_line)
{
    switch (fork())
    {
        case -1:
            perror("fork");
            break;
        case 0:/*child scope*/
            if (execve(path, cmd_line, environ) == -1)
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

