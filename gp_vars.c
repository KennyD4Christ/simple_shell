#include "shell.h"

/**
 * is_rope - test if current char in buffer is a chain delimeter
 * @shell_info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_rope(shell_info_t *shell_info, char *buf, size_t *p)
{
	size_t y = *p;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		shell_info->cmd_buf_type = KMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		shell_info->cmd_buf_type = KMD_AND;
	}
	else if (buf[y] == ';') /* found end of this command */
	{
		buf[y] = 0; /* replace semicolon with null */
		shell_info->cmd_buf_type = KMD_ROPE;
	}
	else
		return (0);
	*p = y;
	return (1);
}

/**
 * check_rope - checks we should continue chaining based on last status
 * @shell_info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @x: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_rope(shell_info_t *shell_info, char *buf, size_t *p, size_t x,
size_t len)
{
	size_t y = *p;

	if (shell_info->cmd_buf_type == KMD_AND)
	{
		if (shell_info->status)
		{
			buf[x] = 0;
			y = len;
		}
	}
	if (shell_info->cmd_buf_type == KMD_OR)
	{
		if (!shell_info->status)
		{
			buf[x] = 0;
			y = len;
		}
	}

	*p = y;
}

/**
 * rep_alias - replaces an aliases in the tokenized string
 * @shell_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(shell_info_t *shell_info)
{
	int x;
	lister *node;
	char *p;

	for (x = 0; x < 10; x++)
	{
		node = nodeBeginsWith(shell_info->alias, shell_info->argv[0], '=');
		if (!node)
			return (0);
		free(shell_info->argv[0]);
		p = stringchr(node->str, '=');
		if (!p)
			return (0);
		p = stringdup(p + 1);
		if (!p)
			return (0);
		shell_info->argv[0] = p;
	}
	return (1);
}

/**
 * rep_vars - replaces vars in the tokenized string
 * @shell_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(shell_info_t *shell_info)
{
	int x = 0;
	lister *node;

	for (x = 0; shell_info->argv[x]; x++)
	{
		if (shell_info->argv[x][0] != '$' || !shell_info->argv[x][1])
			continue;

		if (!stringcmp(shell_info->argv[x], "$?"))
		{
			rep_str(&(shell_info->argv[x]),
				stringdup(con_num(shell_info->status, 10, 0)));
			continue;
		}
		if (!stringcmp(shell_info->argv[x], "$$"))
		{
			rep_str(&(shell_info->argv[x]),
				stringdup(con_num(getpid(), 10, 0)));
			continue;
		}
		node = nodeBeginsWith(shell_info->env, &shell_info->argv[x][1], '=');
		if (node)
		{
			rep_str(&(shell_info->argv[x]),
				stringdup(stringchr(node->str, '=') + 1));
			continue;
		}
		rep_str(&shell_info->argv[x], stringdup(""));

	}
	return (0);
}

/**
 * rep_str - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
