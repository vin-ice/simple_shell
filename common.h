#ifndef COMMON_H
#define COMMON_H

#include <limits.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

#include "env.h"

#define PATH_MAX 4096

/**
 * struct shell_s - shell context structure
 * @program: program name
 * @env: environment variables bucket
 */
typedef struct shell_s
{
	char *program;
	envs_t env;
	void *cmds;
} shell_t;

void free_shell(shell_t *shell);

#endif

