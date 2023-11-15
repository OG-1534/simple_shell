#include "simple_shell.h"

/**
 * inst_buffer - Rd input file
 * @info: struct
 * @buf: pointr to input
 * @len: poitnr to len var
 *
 * Return: bytes
 */

ssize_t inst_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t q = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintOperator);
#if USE_GETLINE
		q = getline(buf, &len_p, stdin);
#else
		q = fetch_line(info, buf, &len_p);
#endif
		if (q > 0)
		{
			if ((*buf)[q - 1] == '\n')
			{
				(*buf)[q - 1] = '\0';
				q--;
			}
			info->countline_flag = 1;
			delete_cmts(*buf);
			createhist_list(info, *buf, info->count_hist++);
			{
				*len = q;
				info->command_buff = buf;
			}
		}
	}
	return (q);
}

/**
 * inpt_ftch - get inpt, except newline char
 * @info: parameter strct
 *
 * Return: bytes
 */
ssize_t inpt_ftch(info_t *info)
{
	static char *buf;
	static size_t t, k, len;
	ssize_t q = 0;
	char **buf_p = &(info->arg), *s;

	put_char(BUF_FLUSH);
	q = insert_buf(info, &buf, &len);
	if (q == -1)
		return (-1);
	if (len)
	{
		k = t;
		s = buf + t;

		test_chain(info, buf, &k, t, len);
		while (k < len)
		{
			if (chain_confirm(info, buf, &k))
				break;
			k++;
		}

		t = k + 1;
		if (t >= len)
		{
			t = len = 0;
			info->command_buff_type = CMD_NORM;
		}

		*buf_p = s;
		return (str_len(p));
	}

	*buf_p = buf;
	return (q);
}

/**
 * buf_scan - Rd info to buf
 * @info: parameter struct
 * @buf: buf to rd
 * @t: pnt to size.
 *
 * Return: bytes
 */
ssize_t buf_scan(info_t *info, char *buf, size_t *t)
{
	ssize_t q = 0;

	if (*t)
		return (0);
	q = read(info->read_fd, buf, READ_BUF_SIZE);
	if (q >= 0)
		*t = q;
	return (q);
}

/**
 * fetch_line - Rd line of input
 * @info: param structure
 * @ptr: pnt address to buf
 * @length: preallocated pointer buf
 *
 * Return: char num or -1 if fail
 */
int fetch_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t t, len;
	size_t j;
	ssize_t q = 0, p = 0;
	char *s = NULL, *new_p = NULL, *d;

	s = *ptr;
	if (s && length)
		p = *length;
	if (t == len)
		t = len = 0;

	q = scan_buffer(info, buf, &len);
	if (q == -1 || (q == 0 && len == 0))
		return (-1);

	d = str_char(buf + i, '\n');
	j = d ? 1 + (unsigned int)(d - buf) : len;
	new_p = re_alloc(s, p, p ? p + j : j + 1);
	if (!new_p)
		return (s ? free(s), -1 : -1);

	if (p)
		strn_cat(new_p, buf + t, j - t);
	else
		strn_cpy(new_p, buf + t, j - t + 1);

	p += j - t;
	t = j;
	s = new_p;

	if (length)
		*length = p;
	*ptr = s;
	return (p);
}

/**
 * Operator_signt - get SIGINT signal
 * @sig_num: unused signal num
 *
 * Return: 0
 */
void Operator_signt(__attribute__((unused))int sig_num)
{
	puts_("\n");
	puts_("$ ");
	put_char(BUF_FLUSH);
}
