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
	fprintf(stderr, "[line %d] Error ", token->line);
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
static void parse_line(parser_t *parser, scanner_t *scanner, cmds_t *cmds);

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
 * parse_line - parses line
 * @parser: parser's context structure
 * @scanner: scanner's context structure
 * @cmds: command lines' bucket
 */
static void parse_line(parser_t *parser, scanner_t *scanner, cmds_t *cmds)
{
	cmd_t line;

	line.capacity = 0;
	line.count = 0;
	line.items = NULL;

	while (1)
	{
		if (parser->current.type == TOKEN_IDENTIFIER)
		{
			printf("line: %*.s",
					(int) parser->current.length,
					parser->current.start);
			write_line(&line, &parser->current);
			printf("%s\n", parser->current.start);
			advance(parser, scanner);
		} else if (parser->current.type == TOKEN_ERROR)
		{
			free_cmds(cmds);
			free(line.items);
			error_at(parser, &parser->current);
			return;
		} else
		{
			break;
		}
	}
	write_cmd_line(cmds, &line);
	add_operation(cmds, OP_SIMPLE);
}

/**
 * parse_program - parses the program
 * @parser: parser's context structure
 * @scanner: scanner's context structure
 * @cmds: command lines bucket
 */
static void parse_program(parser_t *parser, scanner_t *scanner, cmds_t *cmds)
{
	while (parser->current.type != TOKEN_EOF)
	{
		parse_line(parser, scanner, cmds);
	}
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

	init_scanner(&scanner, source);

	parser.errored = false;
	parser.panic_mode = false;

	advance(&parser, &scanner);
	parse_program(&parser, &scanner, cmds);
	return (!parser.errored);
}

