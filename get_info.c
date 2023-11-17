#include "simple_shell.h"
/**
 * wp_info - initialize structure
 * @info: address to the structure
 */

void wp_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * info_plc - initialize a structure
 * @info: address to the structure
 * @av: argument of structure
 */

void info_plc(info_t *info, char **av)
{
	int t = 0;

	info->f_name = av[0];
	if (info->arg)
	{
		info->argv = string_split(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (t = 0; info->argv && info->argv[t]; t++)
			;
		info->argc = t;

		chg_als(info);
		variable_change(info);
	}
}

/**
 * rls_information - release memory for a structure
 * @info: address to the structure
 * @all: bln highlighting need to free fields
 *
 */

void rls_information(info_t *info, int all)
{
	str_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			rls_ls(&(info->env));
		if (info->history)
			rls_ls(&(info->history));
		if (info->alias)
			rls_ls(&(info->alias));
		str_array(info->environ);
			info->environ = NULL;
		free_me((void **)info->cmd_buf);
		if (info->read_fd > 2)
			close(info->read_fd);
		put_char(BUF_FLUSH);
	}
}
