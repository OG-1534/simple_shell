#include "simple_shell.h"

/**
 * inter_active - ascertain whether the shell is interactive
 *
 * @info: struct pointer of shell info.
 *
 * Return: 1 or 0 on failure
 */

int inter_active(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * delimit_check - find delimiters
 *
 * @d: character
 * @delimit: delim str
 *
 * Return: 1 if char is a delim, 0 on failure
 */

int delimit_check(char d, char *delimit)
{
	while (*delimit)
		if (*delimit++ == d)
			return (1);
	return (0);
}

/**
 * alpha_check - ascertain whether a char is alphabetic
 *
 * @d: check char
 *
 * Return: 1 when char is alphhabetic, 0 failure
 */

int alpha_check(int d)
{
	if ((d >= 97 && d <= 122) || (d >= 65 && d <= 90))
		return (1);
	else
		return (0);
}

/**
 * atom_izer - make the string an integer
 * @p: str converted
 * Return: inter on success, 0 failure
 */

int atom_izer(char *p)
{
	unsigned int result = 0;
	int t, sign = 1, flag = 0, output;

	for (t = 0;  p[t] != '\0' && flag != 2; t++)
	{
		if (p[t] == '-')
			sign *= -1;
		if (p[t] >= '0' && p[t] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (p[t] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
