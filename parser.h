#ifndef PARSER_H
#define PARSER_H

#include <string.h>
#include <sys/types.h>

#include "cmd.h"
#include "common.h"
#include "_string.h"
#include "scanner.h"

/**
 * struct parser_s - parser's context structure
 * @previous: previously 'parsed' token
 * @current: token being parsed
 * @errored: state of parser
 * @panic_mode: signifies whether parser has already encountered an error
 */
typedef struct parser_s
{
	token_t previous;
	token_t current;
	bool errored;
	bool panic_mode;
} parser_t;

extern parser_t parser;

bool parse(cmds_t *cmds, char *source);

#endif

