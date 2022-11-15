#include "shell.h"
void _execute(cmd_t *cmd);
int __exit(cmd_t *cmd)
{
    exit (cmd->args);
}
int _env(cmd_t *cmd)
{
    cmd->cmd = "/usr/bin/env";
    _excute(cmd);
    return (1);
}
int _setenv(cmd_t *cmd)
{
    if (setenv(cmd->args[0], (const char)cmd->args[1], (int) cmd->args[2]) == -1)
        perror("setenv");
    return (1);
}
int _unsetenv(cmd_t *cmd)
{
    if (unsetenv(cmd->args) == -1)
        perror("ensetenv");
    return (1);
}
int _cd(cmd_t *cmd)
{
    cmd->cmd = "/"
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