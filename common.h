#ifndef COMMON_H
#define COMMON_H

#include <limits.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

#include "cmd.h"

extern char **environ;

/**
 * struct shell_s - shell context structure
 * @program: program name
 * @cmds: cmd lines bucket
 */
typedef struct shell_s
{
	char *program;
	cmds_t *cmds;
} shell_t;

void free_shell(shell_t *shell);

#endif

