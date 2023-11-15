#include "simple_shell.h"

/**
 * str_comp - compares strings lexicographically.
 *
 * @s1: first string pointer
 * @s2: second string pointer.
 *
 * Return: 0 if s1 equals s2, positive value
 *  if s1 is after s2, negative if s1 is before s2
 */
int str_comp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * str_cat - concatenates two strings.
 * @dst: destination pointer.
 * @src: source pointer.
 *
 * Return: destination pointer after concatenation.
 */
char *str_cat(char *dst, char *src)
{
	char *rt = dst;

	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return (rt);
}
/**
 * str_len - gets a strings length.
 * @p: string pointer to get length
 *
 * Return: integer.
 */
int str_len(char *p)
{
	int t = 0;

	if (!p)
		return (0);

	while (*p++)
		t++;
	return (t);
}
/**
 * starting_string - begins haystack string
 * after needle substring
 *
 * @nedle: The substring to look for at the start of the haystack.
 * @hstack: The string to search within.
 *
 * Return: pointer to next char in the
 * or NULL
 */
char *starting_string(const char *hstack, const char *nedle)
{
	while (*nedle)
		if (*nedle++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}
