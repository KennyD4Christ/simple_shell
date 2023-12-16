#include "shell.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 *
 * Return: 1 on error and 0 on success
 */
int main(int argc, char **argv)
{
	shell_info_t shell_info[] = { SHELL_INFO_T_INIT };
	int find = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (find)
		: "r" (find));

	if (argc == 2)
	{
		find = open(argv[1], O_RDONLY);
		if (find == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				errputs(argv[0]);
				errputs(": 0: Can't open ");
				errputs(argv[1]);
				errputch('\n');
				errputch(BUF_FLU);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shell_info->readfd = find;
	}
	fill_envi_list(shell_info);
	rd_hist(shell_info);
	hshell(shell_info, argv);
	return (EXIT_SUCCESS);
}
