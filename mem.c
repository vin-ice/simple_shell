#include <stdio.h>
#include "_string.h"

#include "mem.h"

/**
 * allocate - resizes dynamic memory
 * @pointer: pointer to previous dyanamic mem
 * @old_size: size of mem pointed to by pointer
 * @new_size: size for new mem
 *
 * Return: pointer to dynamic mem
 */
void *allocate(void *pointer, size_t old_size, size_t new_size)
{
	void *block = NULL;

	(void) old_size;

	if (new_size == 0)
	{
		free(pointer);
		return (NULL);
	}

	block = realloc(pointer, new_size);
	if (block == NULL)
	{
		perror("realloc");
		return (NULL);
	}

	return (block);
}

