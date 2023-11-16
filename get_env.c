#include "simple_shell.h"

/**
 * envn_get - string array with env var.
 * @info: Strc information,
 *
 * Return: 0.
 */

char **envn_get(info_t *info)
{
	if (!info->environ || info->env_chg)
	{
		info->environ = change_list(info->env);
		info->env_chg = 0;
	}

	return (info->environ);
}

/**
 * un_setenv - Delete an envn var
 * @info: Strc with info
 *
 * @var: name for env var
 * Return: 1 when deleted, else 0.
 */

int un_setenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t t = 0;
	char *s;

	if (!node || !var)
		return (0);

	while (node)
	{
		s = starting_string(node->str, var);
		if (s && *s == '=')
		{
			info->env_chg = rmv_node(&(info->env), t);
			t = 0;
			node = info->env;
			continue;
		}
														node = node->next;
		t++;
	}
	return (info->env_chg);
}

/**
 * setenv_ - new env var or update
 * @info: Strc with info
 * @var: name for env var
 * @value: value for the env var
 * Return: 0
 */

int setenv_(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *s;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env;
	while (node)
	{
		s = starting_string(node->str, var);
		if (s && *s == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_chg = 1;
			return (0);
		}
		node = node->next;
	}
	atch_node(&(info->env), buf, 0);
	free(buf);
	info->env_chg = 1;
	return (0);
}
