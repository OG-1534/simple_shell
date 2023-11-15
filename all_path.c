#include "simple_shell.h"
/**
 * verify_command - ascertain whether a file in a pth is executable
 *
 * @info: structure pointer
 * @pth: file path.
 *
 * Return: 1 on success or 0 on failure
 */
int verify_command(info_t *info, char *pth)
{
	struct stat s_t;

	(void)info;
	if (!pth || stat(pth, &s_t))
		return (0);

	if (s_t.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * character_clone - chars on a path string
 *
 * @pathstr: path str of an input
 * @strt: where the index starts
 * @stp: where the index stops
 * Return: buf pointer
 */
char *character_clone(char *pathstr, int strt, int stp)
{
		static char buf[1024];
		int t = 0, j = 0;

		for (j = 0, t = strt; t < stp; t++)
			if (pathstr[t] != ':')
				buf[j++] = pathstr[t];
		buf[j] = 0;
		return (buf);
}

/**
 * findout_path - detect command pth in a str
 *
 * @info: structure pointer
 * @pathstr: directory of the string path
 * @command: cmd
 * Return: pointer of the command
 */
char *findout_path(info_t *info, char *pathstr, char *command)
{
	int t = 0, present_post = 0;
	char *pth;

	if (!pathstr)
		return (NULL);
	if ((str_len(command) > 2) && starting_string(command, "./"))
	{
		if (verify_command(info, command))
			return (command);
	}
	while (1)
	{
		if (!pathstr[t] || pathstr[t] == ':')
		{
			pth = character_clone(pathstr, present_post, t);
			if (!*pth)
				str_cat(pth, command);
			else
			{
				str_cat(pth, "/");
				str_cat(pth, command);
			}
			if (verify_command(info, pth))
				return (pth);
			if (!pathstr[t])
				break;
			present_post = t;
		}
		t++;
	}
	return (NULL);
}
