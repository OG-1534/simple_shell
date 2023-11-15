#include "simple_shell.h"

/**
 * list_output - outputs all linked list elements.
 * @h: pointer to head
 *
 * Return: elements in list
 */
size_t list_output(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		puts_(num_change(h->num, 10, 0));
		put_char(':');
		put_char(' ');
		puts_(h->str ? h->str : "(nil)");
		puts_("\n");
		h = h->next;
		t++;
	}
	return (t);
}
/**
 * len_list - outputs length of linked list
 * @h: pointer to head
 *
 * Return: length of list
 */
size_t len_list(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		h = h->next;
		t++;
	}
	return (t);
}
/**
 * start_node - finds node's beginning prefix
 * @node: node to search prefix
 * @prefix: string to search prefix
 * @c: char following the prefix
 *
 * Return: node or NULL
 */
list_t *start_node(list_t *node, char *prefix, char c)
{
	char *s = NULL;

	while (node)
	{
		s = starting_string(node->str, prefix);
		if (s && ((c == -1) || (*s == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_node_ind - finds a node within a linked list
 * @head: pointer to head
 * @node: node to find
 *
 * Return: node pointer or -1
 */
ssize_t get_node_ind(list_t *head, list_t *node)
{
	size_t t = 0;

	while (head)
	{
		if (head == node)
			return (t);
		head = head->next;
		t++;
	}
	return (-1);
}
/**
 * change_list - makes strings array from list.
 * @head: head pointer
 *
 * Return: strings array or NULL
 */
char **change_list(list_t *head)
{
	list_t *node = head;
	size_t t = len_list(head), k;
	char **sstr;
	char *str;

	if (!head || !t)
		return (NULL);
	sstr = malloc(sizeof(char *) * (t + 1));
	if (!sstr)
		return (NULL);
	for (t = 0; node; node = node->next, t++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < t; k++)
				free(sstr[k]);
			free(sstr);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		sstr[t] = str;
	}
	sstr[t] = NULL;
	return (sstr);
}
