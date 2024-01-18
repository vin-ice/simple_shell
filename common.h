#ifndef COMMON_H
#define COMMON_H

#include <limits.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

#include "env.h"
#include "cmd.h"

#define PATH_MAX 4096
extern char **environ;

/**
 * struct shell_s - shell context structure
 * @program: program name
 * @envs: environment variables bucket
 * @cmds: cmd lines bucket
 */
typedef struct shell_s
{
	char *program;
	envs_t *envs;
	cmds_t *cmds;
} shell_t;

void free_shell(shell_t *shell);

#endif

