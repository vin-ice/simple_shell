#ifndef _STRINGS_H
#define _STRINGS_H

#include <sys/types.h>

char *_strcat(char *str1, const char *str2);
char *_strncat(char *dest, const char *src, int n);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, int n);
char *_strtok_r(char *str, const char *sep, char **saveptr);
char *_strtok(char *str, const char *delim);
size_t _strlen(const char *str);
size_t _strnlen(const char *s, size_t n);
char *_strdup(const char *s);
char *_strndup(const char *s, size_t n);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(const char *s, int c);

#endif

