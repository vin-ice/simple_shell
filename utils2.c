#include "utils.h"
/**
 * _is_word - checks if character is word-like
 * @c: character
 * Return: true or false
 */
bool _is_word(const char c)
{
	return (_is_alpha(c) || _is_digit(c) || c == '~' || c == '/' || c == '-');
}

