#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>
#include <sys/types.h>

ssize_t _getline(char **buffer, size_t *n, FILE *stream);
char *read_file(char *pathname);
#endif /**INPUT_H*/
