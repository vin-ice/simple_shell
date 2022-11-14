#include "shell.h"
char *NAME;
/**
 * main - listens for and accepts a command line
 * and executes programs
 * Return: 0
 */
int main(int argc, char *argv[])
{
    char *prompt = "$ ", *input = NULL, **args = NULL;
    size_t n = 0;
    ssize_t nread;
    int i, mode;
    
    NAME = argv[0];
    if (argc != 1)/*no arguments*/
        usage_error("%s", NAME);
    for (;;)
    {
        mode = isatty(STDIN_FILENO);
        if (mode != 1)
            err_exit(NAME);
        printf("%s", prompt);
        nread = getline(&input, &n, stdin);
        if (nread < 0)/*exit cue*/
            err_exit("exit");
        if (_strcmp(input, "\n") == 0) /*input is empty*/
            continue;
        strip_line(input, nread);/*terminate null*/
        
        args = parse_cmd(input);/*tokens*/
        for (i = 0; args[i]; i++)/*-==== free--====*/
            printf("%s\n", args[i]);
        /*exit command*/
        if (strcmp(args[0], "exit") == 0)
            err_exit("exit");
        execute(&(*args));/*try to execute*/
    }
    return (0);
}
