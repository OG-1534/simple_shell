#include "simple_shell.h"

/**
 * free_me - frees allocated memory
 *
 * @ptr: pointer to memory to be freed
 *
 * Return: 1 on success, 0 on failure
 */
int free_me(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
