#include "shell.h"
/**
 * main - listens for and accepts a command line
 * and executes programs
 * Return: 0
 */
int main(int argc, char *argv[], char *envp[])
{
    char *prompt = "$ ", *input = NULL;
    size_t n = 0;
    ssize_t nread;
    struct stat st;

    if (argc != 1)/*no arguments*/
        usage_error("", argv[0]);
    for (;;)
    {
        printf("%s", prompt);
        nread = getline(&input, &n, stdin);
        if (nread < 0)/*exit cue*/
            err_exit("exit");
        parse_line(input, nread);
        if (stat(input, &st) == -1)/*executable doesnot exist*/
            err_msg("%s: No such file or directory\n", argv[0]);
        else
           return (EXIT_SUCCESS);
    }
    return (0);
}
