#include "shell.h"

/**
 * get_envi - returns the string array copy of our environ
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_envi(shell_info_t *shell_info)
{
	if (!shell_info->environ || shell_info->env_changed)
	{
		shell_info->environ = list_2_strs(shell_info->env);
		shell_info->env_changed = 0;
	}

	return (shell_info->environ);
}

/**
 * _unsetenvi - Remove an environment variable
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenvi(shell_info_t *shell_info, char *var)
{
	lister *node = shell_info->env;
	size_t x = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = begins_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			shell_info->env_changed = delNodeAtIndex(&(shell_info->env), x);
			x = 0;
			node = shell_info->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (shell_info->env_changed);
}

/**
 * _setenvi - Initialize a new environment variable,
 *             or modify an existing one
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenvi(shell_info_t *shell_info, char *var, char *value)
{
	char *buf = NULL;
	lister *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buf = malloc(stringlen(var) + stringlen(value) + 2);
	if (!buf)
		return (1);
	stringcpy(buf, var);
	stringcat(buf, "=");
	stringcat(buf, value);
	node = shell_info->env;
	while (node)
	{
		ptr = begins_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			shell_info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(shell_info->env), buf, 0);
	free(buf);
	shell_info->env_changed = 1;
	return (0);
}
