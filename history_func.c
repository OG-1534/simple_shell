#include "simple_shell.h"

/**
 * createhist_list - an entry of a linked lst
 * @info: struct with args
 *
 * @buf: history lst with a string
 * @word_count: determining count_hist
 *
 * Return: 0
 */
int createhist_list(info_t *info, char *buf, int word_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	atch_node(&node, buf, word_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
  * scan_history - data file hist
  * @info: struct param with information
  *
  * Return: history if successful or 0 on failure
  */
int scan_history(info_t *info)
{
	int t, last = 0, word_count = 0;
	ssize_t f_d, redlen, filesize = 0;
	struct stat s_t;
	char *buf = NULL, *folder_name = get_history_file(info);

	if (!folder_name)
		return (0);

	f_d = open(folder_name, O_RDONLY);
	free(folder_name);
	if (f_d == -1)
		return (0);
	if (!fstat(f_d, &s_t))
		filesize = s_t.st_size;
	if (filesize < 2)
		return (0);
	buf = malloc(sizeof(char) * (filesize + 1));
	if (!buf)
		return (0);
	redlen = read(f_d, buf, filesize);
	buf[filesize] = 0;
	if (redlen <= 0)
		return (free(buf), 0);
	close(f_d);
	for (t = 0; t < filesize; t++)
		if (buf[t] == '\n')
		{
			buf[t] = 0;
			createhist_list(info, buf + last, word_count++);
			last = t + 1;
		}
	if (last != t)
		createhist_list(info, buf + last, word_count++);
	free(buf);
	info->count_hist = word_count;
	while (info->count_hist-- >= HIST_MAX)
		rmv_node(&(info->history), 0);
	change_hist(info);
	return (info->count_hist);
}
/**
 * change_hist - history numbers of a linked list
 * @info: struct with args
 *
 * Return: hist count
 */
int change_hist(info_t *info)
{
	list_t *node = info->history;
	int t = 0;

	while (node)
	{
		node->num = t++;
		node = node->next;
	}
	return (info->count_hist = t);
}

/**
 * document_hist - create a data file
 * @info: struct param with info
 *
 * Return: 1 if successful or -1 upon failure
 */
int document_hist(info_t *info)
{
	ssize_t fd;
	char *folder_name = get_history_file(info);
	list_t *node = NULL;

	if (!folder_name)
		return (-1);

	fd = open(folder_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(folder_name);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		outputs_fd(node->str, fd);
		output_fd('\n', fd);
	}
	output_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * get_history_file - obtain pth of the history file
 * @info: struct with info
 *
 * Return: string with a pth of the history file
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = env_get(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cpy(buf, dir);
	str_cat(buf, "/");
	str_cat(buf, HIST_FILE);
	return (buf);
}
