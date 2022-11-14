#include "shell.h"
int __exit(__attribute__((unused))cmd_t *cmd)
{
    return (1);
}
int _env(__attribute__((unused))cmd_t *cmd)
{
    int count;
    
    for (count = 0; environ[count]; count++)
        printf("%s\n", environ[count]);
    return (1);
}