#include "shell.h"

/**
 * wipe_shell_info - initializes shell_info_t struct
 * @shell_info: struct address
 */
void wipe_shell_info(shell_info_t *shell_info)
{
	shell_info->arg = NULL;
	shell_info->argv = NULL;
	shell_info->path = NULL;
	shell_info->argc = 0;
}

/**
 * set_shell_info - initializes shell_info_t struct
 * @shell_info: struct address
 * @av: argument vector
 */
void set_shell_info(shell_info_t *shell_info, char **av)
{
	int x = 0;

	shell_info->fname = av[0];
	if (shell_info->arg)
	{
		shell_info->argv = stringtow(shell_info->arg, " \t");
		if (!shell_info->argv)
		{

			shell_info->argv = malloc(sizeof(char *) * 2);
			if (shell_info->argv)
			{
				shell_info->argv[0] = stringdup(shell_info->arg);
				shell_info->argv[1] = NULL;
			}
		}
		for (x = 0; shell_info->argv && shell_info->argv[x]; x++)
			;
		shell_info->argc = x;

		rep_alias(shell_info);
		rep_vars(shell_info);
	}
}

/**
 * free_shell_info - frees shell_info_t struct fields
 * @shell_info: struct address
 * @all: true if freeing all fields
 */
void free_shell_info(shell_info_t *shell_info, int all)
{
	forkfree(shell_info->argv);
	shell_info->argv = NULL;
	shell_info->path = NULL;
	if (all)
	{
		if (!shell_info->cmd_buf)
			free(shell_info->arg);
		if (shell_info->env)
			freeList(&(shell_info->env));
		if (shell_info->history)
			freeList(&(shell_info->history));
		if (shell_info->alias)
			freeList(&(shell_info->alias));
		forkfree(shell_info->environ);
			shell_info->environ = NULL;
		buf_free((void **)shell_info->cmd_buf);
		if (shell_info->readfd > 2)
			close(shell_info->readfd);
		_putchar(BUF_FLU);
	}
}
