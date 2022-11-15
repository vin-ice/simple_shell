#include "shell.h"
#define BUFF_SIZE 64
#define TOKEN_DELIM " \r\t\n"
/**
 * _getline - reads input from stream, writes it to mem and returns count of input
 * @lineptr: pointer to pointer of address to write to
 * @n: size of allocated mem
 * @stream: source
 * 
 * Return: count of input
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
    int buff;
    char *ptr, *eptr;
    
    if (*lineptr == NULL || *n == 0)
    {
        *n = BUFF_SIZE;
        *lineptr = malloc(sizeof (char) * (*n));
        if (*lineptr == NULL)
        {
            perror("malloc");
            return (-1);
        }
    }  
    for (ptr = *lineptr, eptr = *lineptr + *n;;)
    {
        buff  = fgetc(stream);
        if (buff == -1)
        {
            if (feof(stream))
                return (ptr == *lineptr ? -1 : ptr - *lineptr);
            else
                return (-1);
        }
        *ptr++ = buff;
        if (buff == '\n')
        {
            *ptr = '\0';
            return (ptr - *lineptr);
        }
        if (ptr + 2 >= eptr)
        {
            *n *= 2;
            *lineptr = realloc(*lineptr, sizeof (char) * (*n));
            if (*lineptr == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
    }
    return (ptr - *lineptr);
}
/**
 * read_line - provides for user input
 * Return: returns inputted string
 */
char *read_line(void)
{
    char *input = NULL;
    size_t size = 0;

    _getline(&input, &size, stdin);

    return (input);
}
/**
 * parse_line - breaks string into tokens and loads to tokens
 * @tokens: holds tokens
 * @str: original string
 * @delim: delimiter
 * 
 * Return: void
 */
cmd_t *parse_line(char *src)
{
    int len = BUFF_SIZE;/*64*/
    int count = 0;
    char *token = NULL, **tokens;
    cmd_t *command = malloc(sizeof (struct command));

    /*init tokens*/
    tokens = malloc(sizeof (char *) * len);
    if (tokens == NULL)
        err_exit("Memory not allocated");
    token = _strtok(src, TOKEN_DELIM);
    command->cmd = token;
    while (token != NULL)
    {
        if (count >= len)
        {
            len += BUFF_SIZE;
            tokens = realloc_memory(tokens, len);
        }
        tokens[count] = token;
        count++;
        token = _strtok(NULL, TOKEN_DELIM);
    }
    if (count >= len)
    {
        len += 1;
        tokens = realloc(tokens, len);
    }
    tokens[count] = NULL;
    command->num_args = count;
    command->args = tokens;
    return (command);
}
/**
 * realloc_memory - reallocates memory
 * @mem: memory to reallocate
 * @size: size to allocate
 * 
 * Return: returns pointer
 */
void *realloc_memory(void *mem, ssize_t size)
{
    mem = realloc(mem, sizeof (char *) * size);
    if (!mem)
    {
        perror("realloc");
        exit (EXIT_FAILURE);
    }
    return (mem);
}
/**
 * free_command - frees struct command
 * @cmd: structure
 * Return: void
 */
void free_command(cmd_t *cmd)
{
    free(cmd->args);
    free(cmd);
}
