#include "simple_shell.h"

/**
  * output_fd - writes char 'c' to file descriptor.
  * @c: character to print.
  * @fd: file descriptor to write char
  *
  * Return: 1 on success -1 on error.
  */
int output_fd(char c, int fd)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(fd, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}
/**
  * outputs_fd - prints characters from string.
  *
  * @str: string to print.
  * @fd: file descriptor to write characters.
  *
  * Return: number of char
  */
int outputs_fd(char *str, int fd)
{
	int t = 0;

	if (!str)
		return (0);
	while (*str)
	{
		t += output_fd(*str++, fd);
	}
	return (t);
}
/**
  * output_char - writes the char 'c' to stderr stream.
  *
  * @c: char to print
  * Return: 1 on success, -1 on failure
  */
int output_char(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int t;

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(2, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}
/**
  * output_str - displays a string.
  * @str: string to print.
  *
  * Return: void
  */
void output_str(char *str)
{
	int t = 0;

	if (!str)
		return;
	while (str[t] != '\0')
	{
		output_char(str[t]);
		t++;
	}
}
