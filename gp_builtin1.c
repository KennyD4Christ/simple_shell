#include "shell.h"

/**
 * _gphist - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _gphist(shell_info_t *shell_info)
{
	output_list(shell_info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @shell_info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(shell_info_t *shell_info, char *str)
{
	char *ptr, c;
	int ret;

	ptr = stringchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	ret = delNodeAtIndex(&(shell_info->alias),
		getNodeIndex(shell_info->alias, nodeBeginsWith(shell_info->alias, str, -1)));
	*ptr = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @shell_info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(shell_info_t *shell_info, char *str)
{
	char *ptr;

	ptr = stringchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(shell_info, str));

	unset_alias(shell_info, str);
	return (addNodeEnd(&(shell_info->alias), str, 0) == NULL);
}

/**
 * output_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int output_alias(lister *node)
{
	char *ptr = NULL, *b = NULL;

	if (node)
	{
		ptr = stringchr(node->str, '=');
		for (b = node->str; b <= ptr; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _gpalias - mimics the alias builtin (man alias)
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _gpalias(shell_info_t *shell_info)
{
	int x = 0;
	char *ptr = NULL;
	lister *node = NULL;

	if (shell_info->argc == 1)
	{
		node = shell_info->alias;
		while (node)
		{
			output_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; shell_info->argv[x]; x++)
	{
		ptr = stringchr(shell_info->argv[x], '=');
		if (ptr)
			set_alias(shell_info, shell_info->argv[x]);
		else
			output_alias(nodeBeginsWith(shell_info->alias, shell_info->argv[x], '='));
	}

	return (0);
}
