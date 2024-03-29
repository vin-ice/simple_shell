#include "scanner.h"

/**
 * skip_whitespace - checks if next character is whitespace and advances
 * @scanner: scanner's context structure
 */
void skip_whitespace(scanner_t *scanner)
{
	char c;

	for (;;)
	{
		c = peek(scanner);
		switch (c)
		{
			case ' ':
			case '\r':
			case '\t':
				advance_scanner(scanner);
				break;
			case '\n':
				scanner->line++;
				advance_scanner(scanner);
				break;
			case '#':
			{
				while (peek(scanner) != '\n' && !is_at_end(scanner))
				{
					advance_scanner(scanner);
				}
				break;
			}
			default:
				return;
		}
	}
}

/**
 * make_token - creates a token out of identified word
 * @scanner: scanner's context structure
 * @type: type of identified word
 *
 * Return: returns a token
 */
static token_t make_token(scanner_t *scanner, int type)
{
	token_t token;

	token.type = type;
	token.start = scanner->start;
	token.line = scanner->line;
	token.length = (scanner->current - scanner->start);
	return (token);
}

/**
 * make_error_token - makes an error token
 * @scanner: scanner's context structure
 * @message: message
 * Return: token
 */
static token_t make_error_token(scanner_t *scanner, const char *message)
{
	token_t token;

	token.type = TOKEN_ERROR;
	token.start = message;
	token.length = (int) _strlen(message);
	token.line = scanner->line;

	return (token);
}

/**
 * make_word_token - makes a word/identifier token
 * @scanner: scanner's context structure
 * @type: type of token
 *
 * Return: identifier token
 */
static token_t make_word_token(scanner_t *scanner, int type)
{
	while (!is_at_end(scanner) && !_is_control_operator(peek(scanner)) &&
			!_strchr(" \t\n", peek(scanner)))
	{
		advance_scanner(scanner);
	}
	return (make_token(scanner, type));
}

/**
 * scan - scans source and makes token out of words
 * @scanner: scanner's context structure
 * Return: returns tokens
 */
token_t scan(scanner_t *scanner)
{
	char c;

	skip_whitespace(scanner);
	scanner->start = scanner->current;

	if (is_at_end(scanner))
	{
		return (make_token(scanner, TOKEN_EOF));
	}

	c = advance_scanner(scanner);
	if (!_is_control_operator(c))
	{
		return (make_word_token(scanner, TOKEN_WORD));
	}

	switch (c)
	{
		case '&':
			return (make_token(scanner,
						(match(scanner, '&') ? TOKEN_BIN_AND : TOKEN_UN_AND)));
		case '|':
			return (make_token(scanner,
						(match(scanner, '|') ? TOKEN_BIN_OR  : TOKEN_UN_OR)));
		case ';':
			return (make_token(scanner, TOKEN_SEMI_COLON));
	}
	return (make_error_token(scanner, "unexpected character."));
}

