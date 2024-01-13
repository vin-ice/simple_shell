#ifndef SCANNER_H
#define SCANNER_H

#include "common.h"
#include "_string.h"
#include "utils.h"

/**
 * struct scanner_s - scanner's context structure
 * @start: pointer to starting index of a word in the source
 * @current: pointer to an offset(ed) index of a word in the source
 * @line: line the word appeares in in the source
 */
typedef struct scanner_s
{
	char *start;
	char *current;
	int line;
} scanner_t;

extern scanner_t scanner;

/**
 * enum token_types - token types
 * @TOKEN_ERROR: error
 * @TOKEN_EOF: EOF '\0'
 * @TOKEN_IDENTIFIER: identifier
 * @TOKEN_BIN_AND: &&
 * @TOKEN_BIN_OR: ||
 * @TOKEN_UN_AND: &
 * @TOKEN_UN_OR: |
 * @TOKEN_SEMI_COLON: ';'
 */
enum token_types
{
	TOKEN_ERROR, TOKEN_EOF,
	TOKEN_IDENTIFIER,
	TOKEN_BIN_AND, TOKEN_UN_AND,
	TOKEN_BIN_OR, TOKEN_UN_OR,
	TOKEN_SEMI_COLON
};

/**
 * struct token_s - token structure
 * @type: type of token
 * @start: pointer to first character of token word
 * @length: size of word
 * @line: line where token appears
 */
typedef struct token_s
{
	int type;
	const char *start;
	size_t length;
	int line;
} token_t;

void init_scanner(scanner_t *scanner, char *source);
token_t scan(scanner_t *scanner);
char peek(scanner_t *scanner);
bool match(scanner_t *scanner, char expected);
bool is_at_end(scanner_t *scanner);
void init_scanner(scanner_t *scanner, char *source);
void skip_whitespace(scanner_t *scanner);

#endif

