#include "shell.h"
char *NAME;
/**
 * main - listens for and accepts a command line
 * and executes programs
 * Return: 0
 */
int main(int argc, char *argv[])
{
    char *prompt = "$ ", *input = NULL;
    int mode;
    cmd_t *command;
    
    NAME = argv[0];
    if (argc != 1)/*no arguments*/
        usage_error("%s", NAME);
    for (;;)
    {
        mode = isatty(STDIN_FILENO);
        if (mode != 1)
            err_exit(NAME);
        printf("%s ", prompt);
        input = read_line();
        command = parse_line(input);/*tokens*/
        execute(command);/*try to execute*/
        free_command(command);
        command  = NULL;
        free(input);
        input = NULL;       
    }
    return (0);
}
