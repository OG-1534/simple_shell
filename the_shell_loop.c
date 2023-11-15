#include "simple_shell.h"

/**
 * our_hsh - shell programs main loop func.
 * @info: pointer to structure with shell information.
 * @av: arguments vector
 *
 * Return: 0 on success 1 on error.
 */
int our_hsh(info_t *info, char **av)
{
	int ret_built_in = 0;
	ssize_t q = 0;

	while (q != -1 && ret_built_in != -2)
	{
		wp_info(info);
		if (inter_active(info))
			puts_("$ ");
		output_char(BUF_FLUSH);
		q = inpt_ftch(info);
		if (q != -1)
		{
			info_plc(info, av);
			ret_built_in = action_built_in(info);
			if (ret_built_in == -1)
				find_command(info);
		}
		else if (inter_active(info))
			put_char('\n');
		rls_information(info, 0);
	}
	document_hist(info);
	rls_information(info, 1);
	if (!inter_active(info) && info->state)
		exit(info->state);
	if (ret_built_in == -2)
	{
		if (info->num_err == -1)
			exit(info->state);
		exit(info->num_err);
	}
	return (ret_built_in);
}

/**
 * action_built_in - finds builtin cmds and executes
 *
 * @info: pointer to shell information
 *
 * Return: -1 cmd not found 0 on success
 * 1 on failure -2 to exit.
 */
int action_built_in(info_t *info)
{
	int t, builtin_retriver = -1;
	built_in_table btable[] = {
		{"exit", exodus_new},
		{"env", my_env},
		{"help", aid_help},
		{"history", hist_new},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", new_cd},
		{"alias", new_alias},
		{NULL, NULL}
	};
	for (t = 0; btable[t].type; t++)
		if (str_comp(info->argv[0], btable[t].type) == 0)
		{
			info->count_line++;
			builtin_retriver = btable[t].func(info);
			break;
		}
	return (builtin_retriver);
}

/**
 * find_command - finds acommand then executes it.
 * @info: pointer to shell information.
 *
 * Return: void
 */
void find_command(info_t *info)
{
	int t, j;
	char *pth = NULL;

	info->pth = info->argv[0];
	if (info->countline_flag == 1)
	{
		info->count_line++;
		info->countline_flag = 0;
	}
	for (t = 0, j = 0; info->arg[t]; t++)
		if (!delimit_check(info->arg[t], " \t\n"))
			j++;
	if (!j)
		return;

	pth = findout_path(info, env_get(info, "PATH="), info->argv[0]);
	if (pth)
	{
		info->pth = pth;
		seperate_cmd(info);
	}
	else
	{
		if ((inter_active(info) || env_get(info, "PATH=")
					|| info->argv[0][0] == '/') && verify_command(info, info->argv[0]))
			seperate_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->state = 127;
			output_error(info, "not found\n");
		}
	}
}

/**
 * seperate_cmd - creates a new process to execute a command.
 * @info: shell information pointer
 *
 * Return: void
 */
void seperate_cmd(info_t *info)
{
	pid_t cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("Error:");
		return;
	}
	if (cpid == 0)
	{
		if (execve(info->pth, info->argv, envn_get(info)) == -1)
		{
			rls_information(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->state));
		if (WIFEXITED(info->state))
		{
			info->state = WEXITSTATUS(info->state);
			if (info->state == 126)
				output_error(info, "Access denied\n");
		}
	}
}
