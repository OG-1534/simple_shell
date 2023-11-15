#include "simple_shell.h"

/**
 * str_output -  outputs the element of a  linked list.
 *
 * @h: head pointer.
 *
 * Return: list size
 */
size_t str_output(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		puts_(h->str ? h->str : "(nil)");
		puts_("\n");
		h = h->next;
		t++;
	}
	return (t);
}
/**
 * rls_ls - sets free linked list nodes.
 * @h_ptr: head pointer.
 *
 * Return: nothing
 */
void rls_ls(list_t **h_ptr)
{
	list_t *post_node, *node, *head;

	if (!h_ptr || !*h_ptr)
		return;
	head = *h_ptr;
	node = head;
	while (node)
	{
		post_node = node->next;
		free(node->str);
		free(node);
		node = post_node;
	}
	*h_ptr = NULL;
}
/**
 * atch_start_node - creates a node at the start of a linked list.
 * @head: head pointer
 * @str: string
 * @num: historical index
 *
 * Return: list size
 */
list_t *atch_start_node(list_t **head, const char *str, int num)
{
	list_t *nw_head;

	if (!head)
		return (NULL);
	nw_head = malloc(sizeof(list_t));
	if (!nw_head)
		return (NULL);
	set_memory((void *)nw_head, 0, sizeof(list_t));
	nw_head->num = num;
	if (str)
	{
		nw_head->str = str_dup(str);
		if (!nw_head->str)
		{
			free(nw_head);
			return (NULL);
		}
	}
	nw_head->next = *head;
	*head = nw_head;
	return (nw_head);
}
/**
 * atch_node - creates node at linked list end.
 *
 * @head: head pointer
 * @str: string
 * @num: historical index.
 *
 * Return: list size.
 */
list_t *atch_node(list_t **head, const char *str, int num)
{
	list_t *node, *nw_node;

	if (!head)
		return (NULL);

	node = *head;
	nw_node = malloc(sizeof(list_t));
	if (!nw_node)
		return (NULL);
	set_memory((void *)nw_node, 0, sizeof(list_t));
	nw_node->num = num;
	if (str)
	{
		nw_node->str = str_dup(str);
		if (!nw_node->str)
		{
			free(nw_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = nw_node;
	}
	else
		*head = nw_node;
	return (nw_node);
}
/**
 * rmv_node - deletes node
 * @head: head pointer
 * @index: node to delete index
 *
 * Return: 1 on success 0 on failure.
 */
int rmv_node(list_t **head, unsigned int index)
{
	unsigned int t = 0;
	list_t *pre_node, *node;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (t == index)
		{
			pre_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		t++;
		pre_node = node;
		node = node->next;
	}
	return (0);
}
