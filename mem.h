#ifndef MEM_H
#define MEM_H

#include <stdlib.h>

#define GROW_CAPACITY(capacity)  \
	((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, old_count, new_count) \
	((type *)allocate(pointer, sizeof(type) * (old_count),\
					sizeof(type) * (new_count)))

#define FREE_ARRAY(type, pointer, old_count) \
	allocate(pointer, sizeof(type) * (old_count), 0)

#define LIST_ADD_HEAD(type_, head_, elem_) \
	do {                                   \
		(elem_)->next = (*head_);          \
		*(head_) = (elem_);                \
	} while (0)

#define LIST_ADD_TAIL(type_, head_, elem_)	\
	do {									\
		type_ **h = head_;					\
		while (*h != NULL)					\
		{									\
			h = &(*h)->next;				\
		}									\
		*h = (elem_);						\
	} while (0)

#define LIST_DELETE_TAIL(type_, head_)						\
	do {													\
		type_ **h = head_;									\
		while (*h != NULL && (*h)->next != NULL)			\
		{													\
			h = &(*h)->next;								\
		}													\
		if (*h != NULL)										\
		{													\
			free((*h)->next);								\
			(*h)->next = NULL;								\
		}													\
	} while (0)

#define LIST_FREE(type, head)	\
	do {						\
		while (head != NULL)	\
		{						\
			type *temp = head;	\
			head = head->next;	\
			free(temp);			\
		}						\
	} while (0)

void *allocate(void *pointer, size_t old_size, size_t new_size);

#endif

