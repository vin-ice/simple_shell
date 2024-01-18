#ifndef ENV_H
#define ENV_H

#include <stdbool.h>

/**
 * struct envs_s - dynamic array of env variables
 * @items: Array of variables
 * @capacity: size of list
 * @count: number of items present
 */
typedef struct envs_s
{
	char **items;
	size_t capacity;
	size_t count;
} envs_t;

bool init_env(envs_t **env, char **envp);
void free_env(envs_t *env);
char **get_env_var_addr(envs_t *env, char *name);
char *get_env(envs_t *env, char *name);
bool add_env_var(envs_t *envs, char *var);
#endif
