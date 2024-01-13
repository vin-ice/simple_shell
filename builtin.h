#ifndef BUILTIN_H
#define BUILTIN_H

#include "common.h"

typedef int (*builtin_handler_t)(shell_t *shell, char **argv);

/**
 * struct builtin_s - builtin type
 * @identifier: name used to recognize the build
 * @handler: handler
 */
typedef struct builtin_s
{
	char *identifier;
	builtin_handler_t handler;
} builtin_t;

bool isbuiltin(char *id);
builtin_handler_t get_builtin_handler(char *id);

/**builds.c*/
int __exit(shell_t *shell, char **argv);
int _env(shell_t *shell, char **argv);
int _setenv(shell_t *shell, char **argv);
int _unsetenv(shell_t *shell, char **argv);
int _cd(shell_t *shell, char **argv);

#endif /*BUILTIN_H*/

