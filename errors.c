#include "shell.h"
/**
 * err_msg - prints an error message on the stdout
 * @str: Error message
 * Return: void
 */
void err_msg(char *format, ...)
{
    va_list va;

    va_start(va, format);
    vprintf(format, va);
    va_end(va);
}
/**
 * err_exit - prints message to stdout and exits program
 * @str: message
 * Return: void
 */
void err_exit(char *str)
{
    printf("\n%s\n", str);
    exit(EXIT_FAILURE);
}
/**
 * usage_error - prints 'Usage' followed by formatted output
 * and exits
 * @format: string to print
 * Return: void
 */
void usage_error(char *format, ...)
{
    va_list va;
    char *s;

    printf("Usage: ");
    va_start(va, format);
    for (; (s = va_arg(va, char *));)
        printf("%s ", s);
    printf(format, va);
    va_end(va);
    printf("\n");
    exit (EXIT_FAILURE);
}