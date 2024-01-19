#include <sys/types.h>
#include <stdio.h>

#include "cmd.h"
#include "common.h"
#include "mem.h"
#include "_string.h"

/**
 * init_cmds - initializes cmds
 * @cmds: cmd lines bucket
 */
void init_cmds(cmds_t *cmds)
{
	cmds->ops = NULL;
	cmds->lines = NULL;
	cmds->count = 0;
	cmds->capacity = 0;
}

/**
 * free_cmd - free cmd;
 * @cmd: cmd line
 */
static void free_cmd(cmd_t *cmd)
{
	size_t i = 0;

	if (cmd)
	{
		if (*cmd->items)
		{
			for (i = 0; i < cmd->count; i++)
			{
				free(cmd->items[i]);
			}
		}
		FREE_ARRAY(char **, cmd->items, cmd->capacity);
		free(cmd);
	}
}

/**
 * free_cmds - frees cmds;
 * @cmds_ptr: pointer to cmds bucket
 */
void free_cmds(cmds_t **cmds_ptr)
{
	size_t i = 0;
	cmds_t *cmds = *cmds_ptr;

	if (cmds)
	{
		if (cmds->lines)
		{
			for (i = 0; i < cmds->count; i++)
			{
				free_cmd(cmds->lines[i]);
			}
			FREE_ARRAY(cmd_t, cmds->lines, cmds->capacity);
		}
		LIST_FREE(op_t, cmds->ops);
		free(cmds);
		*cmds_ptr = NULL;
	}
}

/**
 * write_line - includes a lexeme to a line
 * @line: dynamic array for words
 * @token: token struct
 */
void write_line(cmd_t *line, token_t *token)
{
	size_t old_capacity = line->capacity;


	if (line->capacity < line->count + 2)
	{
		line->capacity = GROW_CAPACITY(old_capacity);
		line->items = GROW_ARRAY(char *, line->items, old_capacity,
								line->capacity);
		if (line->items == NULL)
		{
			return;
		}
	}

	line->items[line->count] = _strndup(token->start, token->length);
	line->items[line->count + 1] = NULL;
	line->count++;
}

/**
 * write_cmd_line - adds a cmd_line into the cmds bucket
 * @cmds: cmds' bucket
 * @line: cmd line
 */
void write_cmd_line(cmds_t *cmds, cmd_t *line)
{
	size_t old_capacity = 0;

	if (cmds->capacity < cmds->count + 2)
	{
		old_capacity = cmds->capacity;
		cmds->capacity = GROW_CAPACITY(old_capacity);
		cmds->lines = GROW_ARRAY(cmd_t *, cmds->lines,
								old_capacity, cmds->capacity);
	}

	cmds->lines[cmds->count] = line;
	cmds->lines[cmds->count + 1] = NULL;
	cmds->count++;
}

