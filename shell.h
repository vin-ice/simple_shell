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
typedef struct aliases{
    char *alias_name;
    char *real_name;
} alias_t;
typedef struct builtins{
    char *name;
    int (*f)(void);
}builtins_t;
int _putchar(char *);
/*helper functions*/
void strip_line(char *str, ssize_t);
char **parse_cmd(char *src);
/*execution interface*/
int execute(char **);
int isexec(char **);
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
void __exit();
#endif /*_SHELL_H_*/