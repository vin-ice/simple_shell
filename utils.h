#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdlib.h>

#include "_string.h"

bool _is_alpha(const char c);
bool _is_digit(const char c);
bool _is_abs(const char *input);
bool _is_path(const char *input);
char *join_path(const char *base, const char *part);
bool _is_word(const char c);
bool _is_name(char c);
bool _is_control_operator(char c);
char *mk_string(size_t size, ...);

#endif

