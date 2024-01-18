#include "utils.h"
/**
 * _is_word - checks if character is word-like
 * @c: character
 * Return: true or false
 */
bool _is_word(const char c)
{
	return (_is_alpha(c) || _is_digit(c) || c == '_' ||
			c == '~' || c == '.' || c == '/' || c == '?' || c == '-');
}

/**
 * _is_name - checks if character consists only of alphanumerics and underscore
 * @c: character
 * Return: true else false
 */
bool _is_name(char c)
{
	return (_is_alpha(c) || _is_digit(c) || c == '_');
}

/**
 * _is_control_operator - checks if character is a control operator
 * @c: character
 * Return: true else false
 */
bool _is_control_operator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '\n');
}
