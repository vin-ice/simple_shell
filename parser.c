#include <stdio.h>

#include "parser.h"
#include "mem.h"

/**
 * error_at - reports an error message
 * @parser: parser's context structure
 * @token: error token
 */
static void error_at(parser_t *parser, token_t *token)
{
	if (parser->panic_mode)
	{
		return;
	}

	parser->panic_mode = true;
	fprintf(stderr, "[line %lu] Error ", token->line);
	fprintf(stderr, "at '%.*s'", (int) token->length, token->start);
	fprintf(stderr, ": %s\n", token->start);
	parser->errored = true;
}

/**
 * advance - probes scanner to scan next token
 * @parser: parser's context structure
 * @scanner: scanner's context structure
 */
static void advance(parser_t *parser, scanner_t *scanner)
{
	parser->previous = parser->current;

	for (;;)
	{
		parser->current = scan(scanner);
		if (parser->current.type != TOKEN_ERROR)
		{
			break;
		}
		error_at(parser, &parser->current);
	}
}

/**
 * add_operation - adds an operation to cmds
 * @cmds: cmds
 * @op_value: value
 */
void add_operation(cmds_t *cmds, int op_value)
{
	op_t *op = NULL;

	op = (op_t *) malloc(sizeof(op_t));
	if (op == NULL)
	{
		perror("add_operation: malloc");
		exit(EXIT_FAILURE);
	}

	op->value = op_value;
	op->next = NULL;
	LIST_ADD_TAIL(op_t, &cmds->ops, op);
}

/**
 * make_line - makes an empty line
 * @cmds: cmd lines bucket
 * Return: return cmd_t line
 */
cmd_t *make_line(cmds_t *cmds)
{
	cmd_t *line = 0;

	line = (cmd_t *) malloc(sizeof(cmd_t));
	if (line == NULL)
	{
		perror("make_line: malloc");
		return (NULL);
	}
	line->count = 0;
	line->capacity = 0;
	line->items = NULL;

	write_cmd_line(cmds, line);
	return (cmds->lines[cmds->count - 1]);
}

/**
 * parse - parses source string
 * @source: source string
 * @cmds: linked list of cmd lines
 * Return: false in case of errors else true
 */
bool parse(cmds_t *cmds, char *source)
{
	parser_t parser;
	scanner_t scanner;
	cmd_t *line = NULL;

	init_scanner(&scanner, source);

	parser.errored = false;
	parser.panic_mode = false;

	for (;;)
	{
		advance(&parser, &scanner);
		if (parser.current.type == TOKEN_WORD)
		{
			if (cmds->count < parser.current.line || cmds->count == 0)
			{
				line = make_line(cmds);
			}
			write_line(line, &parser.current);
		} else if (parser.current.type == TOKEN_ERROR)
		{
			error_at(&parser, &parser.current);
		} else if (parser.current.type == TOKEN_EOF)
		{
			add_operation(cmds, OP_SIMPLE);
			break;
		}
	}
	return (!parser.errored);
}

