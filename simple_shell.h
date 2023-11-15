#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* standard header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

/* chaining commands */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* read and write buffers */
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024

/* system getline */
#define USE_STRTOK 0
#define USE_GETLINE 0

/* convert numbers */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* history checker */
#define HIST_MAX     4096
#define HIST_FILE       ".simple_shell_history"

extern char **envn;

/**
 * struct str_list - linked list function
 * @str: string in linked list
 * @num: field number
 * @next: node pointer
 */
typedef struct str_list
{
	char *str;
	int num;
	struct str_list *next;
}
list_t;

/**
 * struct var_info - arguments to pipe to func.
 *
 * @pth: cmd path
 * @env_chg: changed environment
 * @envn: environment
 * @state: executed cmd state
 * @count_hist: history count
 * @read_fd: file descriptor to read from
 * @history: node for history
 * @env: environment copy
 * @f_name: functinon
 * @argv: argument vector
 * @argc: argument count
 * @alias: node for alias
 * @num_err: exit error
 * @command_buff: command buffer pointer
 * @command_buff_type: command type
 * @count_line: counts errors
 * @countline_flag: input count
 * @arg: arguments
 */
typedef struct var_info
{
	char *pth;
	int env_chg;
	char **envn;
	int state;
	int count_hist;
	int read_fd;
	list_t *history;
	list_t *env;
	char *f_name;
	char **argv;
	int argc;
	list_t *alias;
	int num_err;
	char **command_buff;
	int command_buff_type;
	unsigned int count_line;
	int countline_flag;
	char *arg;
} info_t;

/**
 *struct builtin - builtin environ checker
 *@type: checked character
 *@func: checked function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} built_in_table;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, 0, NULL, NULL, 0, NULL, NULL, NULL, NULL, \
	0, 0, 0}

/* prototypes environment functions */
int envn_list_population(info_t *info);
int unset_env(info_t *info);
int set_env(info_t *info);
char *env_get(info_t *info, const char *name);
int my_env(info_t *info);

/* prototypes for get env functions */
char **envn_get(info_t *info);
int un_setenv(info_t *info, char *var);
int setenv_(info_t *info, char *var, char *value);

/* prototypes for get info functions */
void wp_info(info_t *info);
void info_plc(info_t *info, char **av);
void rls_information(info_t *info, int all);

/* prototypes for main functions */
int main(int ac, char **av);

/* prototypes for string token functions */
char **string_split(char *str, char *c);
char **string2_split(char *str, char c);

/* prototypes for get line functions */
ssize_t inst_buffer(info_t *info, char **buf, size_t *len);
ssize_t inpt_ftch(info_t *info);
ssize_t buf_scan(info_t *info, char *buf, size_t *t);
int fetch_line(info_t *info, char **ptr, size_t *length);
void Operator_signt(__attribute__((unused))int sig_num);

/* prototypes for delimiter functions */
int inter_active(info_t *info);
int delimit_check(char d, char *delimit);
int alpha_check(int d);
int atom_izer(char *p);

/* prototypes for string functions */
char *str_cpy(char *dst, char *src);
int put_char(char b);
void puts_(char *str);
char *str_dup(const char *str);

/* prototypes for string two functions */
int str_comp(char *s1, char *s2);
char *str_cat(char *dst, char *src);
int str_len(char *p);
char *starting_string(const char *htack, const char *nedle);

/* prototypes for lists functions */
size_t str_output(const list_t *h);
void rls_ls(list_t **h_ptr);
list_t *atch_start_node(list_t **head, const char *str, int num);
list_t *atch_node(list_t **head, const char *str, int num);
int rmv_node(list_t **head, unsigned int index);

/* prototypes for lists functions */
size_t list_output(const list_t *h);
size_t len_list(const list_t *h);
list_t *start_node(list_t *node, char *prefix, char c);
ssize_t get_node_ind(list_t *head, list_t *node);
char **change_list(list_t *head);

/* prototypes for memory functions */
int free_me(void **ptr);

/* prototypes for memory allocation functions */
char *set_memory(char *p, char byte, unsigned int num);
void *re_alloc(void *ptr, unsigned int pre_size, unsigned int post_size);
void str_array(char **pstr);

/* prototypes for error checking functions */
int output_fd(char c, int fd);
int outputs_fd(char *str, int fd);
int output_char(char c);
void output_str(char *str);
void output_error(info_t *info, char *errs);
int output_int(int input, int fd);
void delete_cmts(char *buf);
int atoi_err(char *p);
char *num_change(long int nm, int base, int flags);

/* prototypes for built in functions */
int exodus_new(info_t *info);
int new_cd(info_t *info);
int aid_help(info_t *info);

/* prototypes for variation functions */
int str_change(char **ol, char *nw);
int variable_change(info_t *info);
void chain_tst(info_t *info, char *buf, size_t *s, size_t t, size_t len);
int chain_confirm(info_t *info, char *buf, size_t *s);
int chg_als(info_t *info);

/* prototypes for built in two functions */
int hist_new(info_t *info);
int alias_reverse(info_t *info, char *str);
int amend_alias(info_t *info, char *str);
int output_alias(list_t *node);
int new_alias(info_t *info);

/* prototypes for substrings */
char *str_char(char *p, char c);
char *strn_copy(char *dst, char *src, int n);
char *strn_cat(char *dst, char *src, int n);

/* prototypes for history functions */
int createhist_list(info_t *info, char *buf, int word_count);
int scan_history(info_t *info);
int document_hist(info_t *info);
char *get_history_file(info_t *info);
int change_hist(info_t *info);

/* prototypes for all path functions */
int verify_command(info_t *info, char *path);
char *character_clone(char *pathstr, int strt, int stp);
char *findout_path(info_t *info, char *pathstr, char *command);

/* proyotypes for shell loop */
int our_hsh(info_t *info, char **av);
int action_built_in(info_t *info);
void find_command(info_t *info);
void seperate_cmd(info_t *info);

#endif
