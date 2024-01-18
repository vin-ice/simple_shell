#include <assert.h>
#include <stdio.h>
#include <string.h>

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

	if (new_size == 0)
	{
		free(pointer);
		return (NULL);
	}

	if (!pointer)
	{
		block = malloc(new_size);
	} else if (new_size <= old_size)
	{
		block = pointer;
	} else
	{
		assert((pointer) && (new_size > old_size));
		block = malloc(new_size);
		if (block)
		{
			memcpy(block, pointer, old_size);
			free(pointer);
		}
	}
	return (block);
}

