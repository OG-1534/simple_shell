#include "simple_shell.h"

/**
 * *set_memory - allocates a constant byte to
 * a memory block.
 * @p: memory block pointer.
 * @byte: memory block byte value.
 * @num: number of bytes.
 * Return: memory block pointer.
 */
char *set_memory(char *p, char byte, unsigned int num)
{
	unsigned int t;

	for (t = 0; t < num; t++)
		p[t] = byte;
	return (p);
}
/**
 * re_alloc - shuffles memory block.
 * @ptr: pointer to former memory block.
 * @pre_size: former memory block size.
 * @post_size: latter memory block size.
 *
 * Return: memory block pointer.
 */
void *re_alloc(void *ptr, unsigned int pre_size, unsigned int post_size)
{
	char *s;

	if (!ptr)
		return (malloc(post_size));
	if (!post_size)
		return (free(ptr), NULL);
	if (post_size == pre_size)
		return (ptr);

	s = malloc(post_size);
	if (!s)
		return (NULL);

	pre_size = pre_size < post_size ? pre_size : post_size;
	while (pre_size--)
		s[pre_size] = ((char *)ptr)[pre_size];
	free(ptr);
	return (s);
}
/**
 * str_array - array of strings is set free
 * @pstr: pointer to the array.
 *
 * Return: void
 */
void str_array(char **pstr)
{
	char **x = pstr;

	if (!pstr)
		return;
	while (*pstr)
		free(*pstr++);
	free(x);
}
