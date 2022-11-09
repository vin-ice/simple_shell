#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
/*helper functions*/
void parse_line(char *, ssize_t);
int isexe(char *);
/*Error Handlers*/
void err_msg(char *, ...);
void err_exit(char *);
void usage_error(char *, ...);
#endif /*_SHELL_H_*/