#ifndef CMD_H
#define CMD_H

#include "common.h"
#include "scanner.h"

/**
 * enum op_type - types of operations for the executor
 * @OP_SIMPLE: simple operation
 * @OP_BIN_AND: && operation
 * @OP_LIST:list operation
 */
enum op_type
{
	OP_SIMPLE,
	OP_BIN_AND,
	OP_LIST
};

/**
 * struct op_s - operation struct
 * @value: value
 * @next: next
 */
typedef struct op_s
{
	int value;
	struct op_s *next;
} op_t;

/**
 * struct cmd_s - command line dynamic array
 * @capacity: capacity
 * @count: count
 * @items: items
 */
typedef struct cmd_s
{
	size_t capacity;
	size_t count;
	char **items;
} cmd_t;

/**
 * struct cmds_s - command lines' bucket
 * @count: number of lines
 * @capacity: cmd capacity
 * @ops: informs the executor of the kind of operation to perform
 * @lines: dynamic array of command lines
 */
typedef struct cmds_s
{
	size_t count;
	size_t capacity;
	op_t *ops;
	cmd_t *lines;
} cmds_t;

void init_cmds(cmds_t *cmds);
void free_cmds(cmds_t *cmds);
void write_line(cmd_t *line, token_t *token);
void write_cmd_line(cmds_t *cmds, cmd_t *line);

#endif

