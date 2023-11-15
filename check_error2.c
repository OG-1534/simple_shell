#include "simple_shell.h"

/**
  * output_error - displays an error message
  *
  * @info: return information
  * @errs: string with error type
  * Return: nothing
  */
void output_error(info_t *info, char *errs)
{
	output_str(info->f_name);
	output_str(": ");
	output_int(info->count_line, STDERR_FILENO);
	output_str(": ");
	output_str(info->argv[0]);
	output_str(": ");
	output_str(errs);
}
/**
  * output_int - prints an int
  *
  * @input: int to print
  * @fd: file descriptor
  *
  * Return: number of characters
  */
int output_int(int input, int fd)
{
	int (*_put_char)(char) = put_char;
	int t, cnt = 0;
	unsigned int curr, _ab_;

	if (fd == STDERR_FILENO)
		_put_char = output_char;
	if (input < 0)
	{
		_ab_ = -input;
		_put_char('-');
		cnt++;
	}
	else
		_ab_ = input;
	curr = _ab_;
	for (t = 1000000000; t > 1; t /= 10)
	{
		if (_ab_ / t)
		{
			_put_char('0' + curr / t);
			cnt++;
		}
		curr %= t;
	}
	_put_char('0' + curr);
	cnt++;
	return (cnt);
}
/**
  * delete_cmts - replaces '#' first instance with '\0'
  * @buf: string address
  *
  * Return: Always 0
  */
void delete_cmts(char *buf)
{
	int t;

	for (t = 0; buf[t] != '\0'; t++)
		if (buf[t] == '#' && (!t || buf[t - 1] == ' '))
		{
			buf[t] = '\0';
			break;
		}
}
/**
  * atoi_err - converts str to int
  * @p: string to convert
  *
  * Return: int or -1 on error
  */
int atoi_err(char *p)
{
	unsigned long int res = 0;
	int t = 0;

	if (*p == '+')
		p++;
	for (t = 0; p[t] != '\0'; t++)
	{
		if (p[t] >= '0' && p[t] <= '9')
		{
			res *= 10;
			res += (p[t] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
/**
  * num_change - num to string converter
  * @num: num to convert
  * @base: conversion base
  * @flags: customization flags
  *
  * Return: string of converted number
  */
char *num_change(long int num, int base, int flags)
{
	char *ptr;
	char sgn = 0;
	static char buff[50];
	static char *arr;
	unsigned long m = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		m = -num;
		sgn = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[m % base];
		m /= base;
	} while (m != 0);

	if (sgn)
		*--ptr = sgn;
	return (ptr);
}
