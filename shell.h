#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
extern char *NAME;/*program name*/
extern char **environ;/*environment variables list*/
typedef struct command{
    int num_args;
    char *cmd;
    char **args;
}cmd_t;
typedef struct aliases{
    char *alias_name;
    char *real_name;
} alias_t;
typedef struct builtins{
    char *name;
    int (*f)(cmd_t *);
}builtins_t;
/*input*/
char *read_line(void);
int _putchar(char *);
void free_command(cmd_t *);
cmd_t *parse_line(char *src);
void *realloc_memory(void *mem, ssize_t size);
/*helper functions*/
void strip_line(char *str, ssize_t);
/*execution interface*/
int execute(cmd_t *);
int isexec(cmd_t *);
/*strings*/
int _strcmp(char *, char *);
int _strncmp(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strcat(char *, char *);
int _strlen(char *);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char );
/*Error Handlers*/
void err_msg(char *format, ...);
void err_exit(char *msg);
void usage_error(char *format, ...);
/*Environment handlers*/
char *_getenv(char *);
/*built-ins*/
int __exit(cmd_t*);
int _env(cmd_t *);
#endif /*_SHELL_H_*/