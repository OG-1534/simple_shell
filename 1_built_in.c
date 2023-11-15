#include "simple_shell.h"

/**
  * exodus_new - exiting the shell
  * @info: struct pointer with args
  * Return: shell exit state
  */
int exodus_new(info_t *info)
{
	int scan_exit;

	if (info->argv[1])
	{
		scan_exit = atoi_err(info->argv[1]);
		if (scan_exit == -1)
		{
			info->state = 2;
			output_error(info, "Illegal number: ");
			output_str(info->argv[1]);
			output_char('\n');
			return (1);
		}
			info->num_err = atoi_err(info->argv[1]);
			return (-2);
		}
			info->num_err = -1;
				return (-2);
}

/**
  * new_cd - replace working directory
  * @info: struct pointer with args
  * Return: 0
  */
int new_cd(info_t *info)
{
	char *p, *dir, buffer[1024];
	int chdir_ret;

	p = getcwd(buffer, 1024);
	if (!p)
		puts_("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = env_get(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what is it? */
				chdir((dir = env_get(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_comp(info->argv[1], "-") == 0)
	{
		if (!env_get(info, "OLDPWD="))
		{
			puts_(p);
			put_char('\n');
			return (1);
		}
		puts_(env_get(info, "OLDPWD=")), put_char('\n');
		chdir_ret =
			chdir((dir = env_get(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		output_error(info, "can't cd to ");
		output_str(info->argv[1]), output_char('\n');
	}
	else
	{
		setenv_(info, "OLDPWD", env_get(info, "PWD="));
		setenv_(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
  * aid_help - show help info
  * @info: struct pointer with args
  * Return: 0
  */
int aid_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	puts_("help call works. Function not yet implemented \n");
	if (0)
		puts_(*arg_array);
	return (0);
}
