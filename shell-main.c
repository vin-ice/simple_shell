#include "shell.h"
/**
 * main - listens for and accepts a command line
 * and executes programs
 * @argc: arguments count
 * @argv: array of pointers to arguments
 * Return: 0
 */
int main(int argc, char *argv[])
{
    char *prompt = "$ ", *input = NULL;
    int mode;
    cmd_t *command;

    if (argc != 1)/*no arguments*/
        usage_error("%s", argv[0]);
    for (;;)
    {
        mode = isatty(STDIN_FILENO);
        if (mode != 1)
            err_exit(argv[0]);
        printf("%s ", prompt);
        input = read_line();
        command = parse_line(input, argv[0]);/*tokens*/
        execute(command);/*try to execute*/
        free_command(command);
        command  = NULL;
        free(input);
        input = NULL;
    }
    return (0);
}
