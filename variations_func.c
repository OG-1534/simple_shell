#include "simple_shell.h"

/**
 * str_change - string to be reolaced
 * @ol: replace old address
 * @nw: used to replace the old string
 *
 * Return: 1 on success, 0 failed.
 */
int str_change(char **ol, char *nw)
{
	free(*ol);
	*ol = nw;
	return (1);
}

/**
 * variable_change - change vars on the str
 * @info: Pointer of param structure.
 *
 * Return: 1 on success or 0 if it fails
 */
int variable_change(info_t *info)
{
	int t = 0;
	list_t *node;

	for (t = 0; info->argv[t]; t++)
	{
		if (info->argv[t][0] != '$' || !info->argv[t][1])
			continue;

		if (!str_comp(info->argv[t], "$?"))
		{
			str_change(&(info->argv[t]),
				str_dup(num_change(info->status, 10, 0)));
			continue;
		}
		if (!str_comp(info->argv[t], "$$"))
		{
			str_change(&(info->argv[t]),
				str_dup(num_change(getpid(), 10, 0)));
			continue;
		}
		node = start_node(info->env, &info->argv[t][1], '=');
		if (node)
		{
			str_change(&(info->argv[t]),
				str_dup(str_char(node->str, '=') + 1));
			continue;
		}
		str_change(&info->argv[t], str_dup(""));

	}
	return (0);
}

/**
 * chain_tst - ascertain whether to continue given the lst cmd
 * @info: Pnt of param struct
 * @buf: buf char.
 * @s: current pst address
 * @t: buf strt pst
 * @len: buf len
 *
 * Return: 0
 */
void chain_tst(info_t *info, char *buf, size_t *s, size_t t, size_t len)
{
	size_t k = *s;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[t] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[t] = 0;
			k = len;
		}
	}

	*s = k;
}

/**
 * chain_confirm - Char in buf
 * @info: param struct pont
 * @buf: buf char
 * @s: but current pst address
 *
 * Return: 1 on success, 0 on failure
 */
int chain_confirm(info_t *info, char *buf, size_t *s)
{
	size_t k = *s;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') /* located at the end of command */
	{
		buf[k] = 0; /* replaced null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*s = k;
	return (1);
}

/**
 * chg_als - change tokenised str
 * @info: struct param
 *
 * Return: replaced, 0 on failure
 */
int chg_als(info_t *info)
{
	int t;
	list_t *node;
	char *s;

	for (t = 0; t < 10; t++)
	{
		node = start_node(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		s = str_char(node->str, '=');
		if (!s)
			return (0);
		s = str_dup(s + 1);
		if (!s)
			return (0);
		info->argv[0] = s;
	}
	return (1);
}
