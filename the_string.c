#include "simple_shell.h"

/**
 * str_cpy - copies a string to destination from source
 *
 * @src: source pointer
 * @dst: destination pointer
 *
 * Return: destination pointer
 */
char *str_cpy(char *dst, char *src)
{
	int a = 0;

	if (dst == src || src == 0)
		return (dst);
	while (src[a])
	{
		dst[a] = src[a];
		a++;
	}
	dst[a] = 0;
	return (dst);
}
/**
 * put_char - writes char c to STDOUT
 *
 * @c: character to print
 *
 * Return: 1 on success and -1 on error
 */
int put_char(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int a;

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}
/**
 * puts_ - prints string to STDOUT
 *
 * @str: string to print
 *
 * Return: nothing
 */
void puts_(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		put_char(str[a]);
		a++;
	}
}
/**
 * str_dup - duplicates strings
 *
 * @str: string to duplicate
 *
 * Return: duplicate string pointer
 */
char *str_dup(const char *str)
{
	char *rt;
	int len_str = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len_str++;
	rt = malloc(sizeof(char) * (length + 1));
	if (!rt)
		return (NULL);
	for (len_str++; len_str--;)
		rt[len_str] = *--str;
	return (rt);
}
