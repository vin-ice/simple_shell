#include <stdio.h>
extern char **environ;
/**
 * main - driver function for tests on _env.c
 * Return - 0 or 1
 */
int main(void)
{
    printf("%s", environ[0]);
    return (0);
}