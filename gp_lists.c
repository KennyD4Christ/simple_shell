#include "shell.h"

/**
 * addNode - adds a node to the start of the list
 * @h: address of pointer to h node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
lister *addNode(lister **h, const char *str, int num)
{
	lister *new_h;

	if (!h)
		return (NULL);
	new_h = malloc(sizeof(lister));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(lister));
	new_h->num = num;
	if (str)
	{
		new_h->str = stringdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *h;
	*h = new_h;
	return (new_h);
}

/**
 * addNodeEnd - adds a node to the end of the list
 * @h: address of pointer to h node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
lister *addNodeEnd(lister **h, const char *str, int num)
{
	lister *new_node, *node;

	if (!h)
		return (NULL);

	node = *h;
	new_node = malloc(sizeof(lister));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(lister));
	new_node->num = num;
	if (str)
	{
		new_node->str = stringdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*h = new_node;
	return (new_node);
}

/**
 * output_list_string - prints only the str element of a lister linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t output_list_string(const lister *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * delNodeAtIndex - deletes node at given index
 * @h: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delNodeAtIndex(lister **h, unsigned int index)
{
	lister *node, *prev_node;
	unsigned int x = 0;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		node = *h;
		*h = (*h)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (x == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * freeList - frees all nodes of a list
 * @h_ptr: address of pointer to h node
 *
 * Return: void
 */
void freeList(lister **h_ptr)
{
	lister *node, *next_node, *h;

	if (!h_ptr || !*h_ptr)
		return;
	h = *h_ptr;
	node = h;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*h_ptr = NULL;
}
