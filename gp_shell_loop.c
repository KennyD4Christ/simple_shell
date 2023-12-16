#include "shell.h"

/**
 * hshell - main shell loop
 * @shell_info: the parameter & return shell_info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hshell(shell_info_t *shell_info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		wipe_shell_info(shell_info);
		if (interactive_mode(shell_info))
			_puts("$ ");
		errputch(BUF_FLU);
		r = get_kmd(shell_info);
		if (r != -1)
		{
			set_shell_info(shell_info, av);
			builtin_ret = search_builtin(shell_info);
			if (builtin_ret == -1)
				search_kmd(shell_info);
		}
		else if (interactive_mode(shell_info))
			_putchar('\n');
		free_shell_info(shell_info, 0);
	}
	w_hist(shell_info);
	free_shell_info(shell_info, 1);
	if (!interactive_mode(shell_info) && shell_info->status)
		exit(shell_info->status);
	if (builtin_ret == -2)
	{
		if (shell_info->err_num == -1)
			exit(shell_info->status);
		exit(shell_info->err_num);
	}
	return (builtin_ret);
}

/**
 * search_builtin - finds a builtin command
 * @shell_info: the parameter & return shell_info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int search_builtin(shell_info_t *shell_info)
{
	int x, built_in_ret = -1;
	sys_builtin_tb builtintbl[] = {
		{"exit", _gpexit},
		{"env", _gpenvi},
		{"help", _gphelp},
		{"history", _gphist},
		{"setenv", _gpsetenvi},
		{"unsetenv", _gpunsetenvi},
		{"cd", _gpcd},
		{"alias", _gpalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (stringcmp(shell_info->argv[0], builtintbl[x].type) == 0)
		{
			shell_info->line_count++;
			built_in_ret = builtintbl[x].func(shell_info);
			break;
		}
	return (built_in_ret);
}

/**
 * search_kmd - finds a command in PATH
 * @shell_info: the parameter & return shell_info struct
 *
 * Return: void
 */
void search_kmd(shell_info_t *shell_info)
{
	char *path = NULL;
	int x, m;

	shell_info->path = shell_info->argv[0];
	if (shell_info->linecount_flag == 1)
	{
		shell_info->line_count++;
		shell_info->linecount_flag = 0;
	}
	for (x = 0, m = 0; shell_info->arg[x]; x++)
		if (!is_delimiter(shell_info->arg[x], " \t\n"))
			m++;
	if (!m)
		return;

	path = search_path(shell_info, _getenvi(shell_info, "PATH="),
			shell_info->argv[0]);
	if (path)
	{
		shell_info->path = path;
		spawn_kmd(shell_info);
	}
	else
	{
		if ((interactive_mode(shell_info) || _getenvi(shell_info, "PATH=")
			|| shell_info->argv[0][0] == '/') && is_kmd(shell_info,
				shell_info->argv[0]))
			spawn_kmd(shell_info);
		else if (*(shell_info->arg) != '\n')
		{
			shell_info->status = 127;
			output_err(shell_info, "not found\n");
		}
	}
}

/**
 * spawn_kmd - forks a an exec thread to run cmd
 * @shell_info: the parameter & return shell_info struct
 *
 * Return: void
 */
void spawn_kmd(shell_info_t *shell_info)
{
	pid_t c_pid;

	c_pid = fork();
	if (c_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (c_pid == 0)
	{
		if (execve(shell_info->path, shell_info->argv, get_envi(shell_info)) == -1)
		{
			free_shell_info(shell_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(shell_info->status));
		if (WIFEXITED(shell_info->status))
		{
			shell_info->status = WEXITSTATUS(shell_info->status);
			if (shell_info->status == 126)
				output_err(shell_info, "Permission denied\n");
		}
	}
}
