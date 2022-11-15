#ifndef _TEST_H_
#define _TEST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

extern char **environ;
char *_getenv(char *);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
#endif /*_TEST_H_*/