#include "simple_shell.h"

/**
  * str_char - finds first occurrence of a char in a str.
  * @p: string to search character.
  * @c: char to search
  *
  * Return: pointer of char or NULL.
  */
char *str_char(char *p, char c)
{
	do {
		if (*p == c)
			return (p);
	} while (*p++ != '\0');
	return (NULL);
}

/**
 * strn_copy - copies a src strings
 * sub strinng to dst string
 * @dst: destination string pointer.
 * @src: source string pointer
 * @n: characters to copy
 *
 * Return: dst string pointer
 */

char *strn_copy(char *dst, char *src, int n)
{
	char *p = dst;
	int t, k;

	t = 0;
	while (src[t] != '\0' && t < n - 1)
	{
		dst[t] = src[t];
		t++;
	}
	if (t < n)
	{
		k = t;
		while (k < n)
		{
			dst[k] = '\0';
			k++;
		}
	}
	return (p);
}
/**
  * strn_cat - concatenates strings.
  *
  * @dst: string concatenated to.
  * @src: string to concatenate.
  * @n: bytes to be used
  *
  * Return: pointer to string.
  */
char *strn_cat(char *dst, char *src, int n)
{
	char *p = dst;
	int t, k;

	t = 0;
	k = 0;
	while (dst[t] != '\0')
		t++;
	while (src[k] != '\0' && k < n)
	{
		dst[t] = src[k];
		t++;
		k++;
	}
	if (k < n)
		dst[t] = '\0';
	return (p);
}
