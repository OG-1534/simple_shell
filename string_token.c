#include "simple_shell.h"

/**
 * **string_split - make an input str to words
 * @str: split input strn
 * @c: delim string to be splitted
 * Return: pointer or NULL
 */
char **string_split(char *str, char *c)
{
	int t, k, j, n, wordnum = 0;
	char **p;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!c)
		c = " ";
	for (t = 0; str[t] != '\0'; t++)
		if (!delimit_check(str[t], c) &&
		(delimit_check(str[t + 1], c)
		 || !str[t + 1]))
			wordnum++;

	if (wordnum == 0)
		return (NULL);
	p = malloc((1 + wordnum) * sizeof(char *));
	if (!p)
		return (NULL);
	for (t = 0, k = 0; k < wordnum; j++)
	{
		while (delimit_check(str[t], c))
			t++;
		j = 0;
		while (!delimit_check(str[t + j], c) && str[t + j])
			j++;
		p[k] = malloc((j + 1) * sizeof(char));
		if (!p[k])
		{
			for (j = 0; j < k; j++)
				free(p[j]);
			free(p);
			return (NULL);
		}
			for (n = 0; n < k; n++)
				p[k][n] = str[t++];
			p[k][n] = 0;
	}
	p[k] = NULL;
	return (p);
}

/**
 * string2_split - split input
 * @str: string input
 * @c: delim char
 * Return: pointer to array or NULL if it fails
 */
char **string2_split(char *str, char c)
{
	int t, k, j, n, wordnum = 0;
	char **p;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (t = 0; str[t] != '\0'; t++)
		if ((str[t] != c && str[t + 1] == c) ||
			(str[t] != c && !str[t + 1]) || str[t + 1] == c)
				wordnum++;
	if (wordnum == 0)
		return (NULL);
	p = malloc((1 + wordnum) * sizeof(char *));
	if (!p)
		return (NULL);
	for (t = 0, k = 0; k < wordnum; k++)
	{
		while (str[t] == c && str[t] != c)
			t++;
		j = 0;
		while (str[t + j] != c && str[t + j] && str[t + j] != c)
			j++;
		p[k] = malloc((j + 1) * sizeof(char));
		if (!p[k])
		{
			for (j = 0; j < k; j++)
				free(p[j]);
			free(p);
			return (NULL);
		}
		for (n = 0; n < j; n++)
			p[k][n] = str[t++];
		p[k][n] = 0;
	}
	p[k] = NULL;
	return (p);
}
