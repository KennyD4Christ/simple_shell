#include "shell.h"

/**
 * _gpexit - exits the shell
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if shell_info.argv[0] != "exit"
 */
int _gpexit(shell_info_t *shell_info)
{
	int exitcheck;

	if (shell_info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(shell_info->argv[1]);
		if (exitcheck == -1)
		{
			shell_info->status = 2;
			output_err(shell_info, "Illegal number: ");
			errputs(shell_info->argv[1]);
			errputch('\n');
			return (1);
		}
		shell_info->err_num = _erratoi(shell_info->argv[1]);
		return (-2);
	}
	shell_info->err_num = -1;
	return (-2);
}

/**
 * _gpcd - changes the current directory of the process
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _gpcd(shell_info_t *shell_info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!shell_info->argv[1])
	{
		dir = _getenvi(shell_info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenvi(shell_info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (stringcmp(shell_info->argv[1], "-") == 0)
	{
		if (!_getenvi(shell_info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenvi(shell_info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenvi(shell_info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shell_info->argv[1]);
	if (chdir_ret == -1)
	{
		output_err(shell_info, "can't cd to ");
		errputs(shell_info->argv[1]), errputch('\n');
	}
	else
	{
		_setenvi(shell_info, "OLDPWD", _getenvi(shell_info, "PWD="));
		_setenvi(shell_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _gphelp - changes the current directory of the process
 * @shell_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _gphelp(shell_info_t *shell_info)
{
	char **arg_array;

	arg_array = shell_info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
