#include "simple_shell.h"
/**
  * hist_new - history of executed cmds.
  * @info: recurrent struct with args
  * Return: 0
  */
int hist_new(info_t *info)
{
	list_output(info->history);
	return (0);
}

/**
  * alias_reverse- string assigned an alias
  *
  * @info: param on a struct
  * @str: string with an alias
  *
  * Return: 0 on success or 1 failure
  */
int alias_reverse(info_t *info, char *str)
{
	char *s, d;
	int rt;

	s = str_char(str, '=');
	if (!s)
		return (1);
	d = *s;
	*s = 0;
	rt = rmv_node(&(info->alias),
			get_node_ind(info->alias, start_node(info->alias, str, -1)));
	*s = d;
	return (rt);
}
/**
 * amend_alias - coupling the alias with a str
 *
 * @info: param on a struct
 * @str: alias str
 *
 * Return: 0 on success or 1 failure
 */
int amend_alias(info_t *info, char *str)
{
	char *s;

	s = str_char(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (alias_reverse(info, str));

	alias_reverse(info, str);
	return (atch_node(&(info->alias), str, 0) == NULL);
}
/**
  * output_alias - output for a str
  *
  * @node: node (alias) with str
  *
  * Return: 0 on success or 1 failure
  */
int output_alias(list_t *node)
{
	char *s = NULL, *x = NULL;

	if (node)
	{
		s = str_char(node->str, '=');
		for (x = node->str; x <= s; x++)
			put_char(*x);
		put_char('\'');
		puts_(s + 1);
		puts_("'\n");
		return (0);
	}
	return (1);
}
/**
  * new_alias - replicates the attribute of a cmd
  *
  * @info: struct with function args
  * Return: 0
  */
int new_alias(info_t *info)
{
	int t = 0;
	char *s = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			output_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (t = 1; info->argv[t]; t++)
	{
		s = str_char(info->argv[t], '=');
		if (s)
			amend_alias(info, info->argv[t]);
		else
			output_alias(start_node(info->alias, info->argv[t], '='));
	}
	return (0);
}
