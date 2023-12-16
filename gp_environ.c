#include "shell.h"

/**
 * _gpenvi - prints the current environment
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _gpenvi(shell_info_t *shell_info)
{
	output_list_string(shell_info->env);
	return (0);
}

/**
 * _getenvi - gets the value of an environ variable
 * @shell_info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenvi(shell_info_t *shell_info, const char *name)
{
	lister *node = shell_info->env;
	char *p;

	while (node)
	{
		p = begins_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _gpsetenvi - Initialize a new environment variable,
 *             or modify an existing one
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _gpsetenvi(shell_info_t *shell_info)
{
	if (shell_info->argc != 3)
	{
		errputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvi(shell_info, shell_info->argv[1], shell_info->argv[2]))
		return (0);
	return (1);
}

/**
 * _gpunsetenvi - Remove an environment variable
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _gpunsetenvi(shell_info_t *shell_info)
{
	int x;

	if (shell_info->argc == 1)
	{
		errputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= shell_info->argc; x++)
		_unsetenvi(shell_info, shell_info->argv[x]);

	return (0);
}

/**
 * fill_envi_list - populates env linked list
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fill_envi_list(shell_info_t *shell_info)
{
	lister *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		addNodeEnd(&node, environ[x], 0);
	shell_info->env = node;
	return (0);
}
