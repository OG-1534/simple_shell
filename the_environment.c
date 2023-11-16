#include "simple_shell.h"

/**
 * envn_list_population - populate the linked enviornment list
 * @info: a structure that has arguments.
 *
 * Return: 0
 */

int envn_list_population(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		atch_node(&node, environ[a], 0);
	info->env = node;
	return (0);

}
/**
 * unset_env - Remove environment variable
 * @info: potential arguments in a structure
 *
 * Return: 0
 */

int unset_env(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		output_str("few arguments.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		un_setenv(info, info->argv[a]);

	return (0);
}

/**
 * set_env - generate en enviornment variable or change one that exists
 * @info: structure with arguments
 *
 * Return: 0
 */

int set_env(info_t *info)
{
	if (info->argc != 3)
	{
		output_str("not the right no of arguments\n");
		return (1);
	}
	if (setenv_(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * env_get - value of the env variable
 * @info: structure with potential args
 * @name: name for env variable
 *
 * Return: value or NULL
 */

char *env_get(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *t;

	while (node)
	{
		t = starting_string(node->str, name);
		if (t && *t)
			return (t);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_env - display env variables
 * @info: structure with args
 *
 * Return: 0
 */

int my_env(info_t *info)
{
	str_output(info->env);
	return (0);
}
