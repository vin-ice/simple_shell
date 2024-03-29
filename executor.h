#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "common.h"

/**
 * enum exec_state - executor exit status
 * @EXEC_OK: ok
 * @EXEC_RUNTIME_ERROR: runtime error
 * @EXEC_PARSE_ERROR: parsing error
 */
enum exec_state
{
	EXEC_OK,
	EXEC_PARSE_ERROR,
	EXEC_RUNTIME_ERROR = 127
};

int execute(shell_t *shell, char *source);

#endif

