#include "scanner.h"

/**
 * init_scanner - initializes scanner
 * @scanner: scanner's context structure
 * @source: null terminated string of user input
 */
void init_scanner(scanner_t *scanner, char *source)
{
	scanner->start = source;
	scanner->current = source;
	scanner->line = 1;
}

/**
 * advance - advances the current pointer to next character
 * @scanner: scanner context structure
 * Return: returns previous character
 */
char advance_scanner(scanner_t *scanner)
{
	scanner->current++;
	return (scanner->current[-1]);
}

/**
 * peek - returns character under the current pointer
 * @scanner: scanner's context structure
 * Return: return the character under the current pointer
 */
char peek(scanner_t *scanner)
{
	return (*scanner->current);
}

/**
 * is_at_end - checks it current cursor points to the terminating characte
 * @scanner: scanner context structure
 * Return: returns true if its a nulle character else false
 */
bool is_at_end(scanner_t *scanner)
{
	return (*scanner->current == '\0');
}

/**
 * match - checks if current points to provided character
 * @scanner: scanner context structure
 * @expected: provided character the is expected
 *
 * Return: true if they are same else false
 */
bool match(scanner_t *scanner, char expected)
{
	if (is_at_end(scanner) || *(scanner->current) != expected)
	{
		return (false);
	}
	scanner->current++;
	return (true);
}

