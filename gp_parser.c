#include "shell.h"

/**
 * is_kmd - determines if a file is an executable command
 * @shell_info: the shell_info structs
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_kmd(shell_info_t *shell_info, char *path)
{
	struct stat st;

	(void)shell_info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_ch - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_ch(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int x = 0, q = 0;

	for (q = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buf[q++] = pathstr[x];
	buf[q] = 0;
	return (buf);
}

/**
 * search_path - finds this kmd in the PATH string
 * @shell_info: the shell_info struct
 * @pathstr: the PATH string
 * @kmd: the kmd to find
 *
 * Return: full path of kmd if found or NULL
 */
char *search_path(shell_info_t *shell_info, char *pathstr, char *kmd)
{
	int x = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((stringlen(kmd) > 2) && begins_with(kmd, "./"))
	{
		if (is_kmd(shell_info, kmd))
			return (kmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			path = dup_ch(pathstr, curr_pos, x);
			if (!*path)
				stringcat(path, kmd);
			else
			{
				stringcat(path, "/");
				stringcat(path, kmd);
			}
			if (is_kmd(shell_info, path))
				return (path);
			if (!pathstr[x])
				break;
			curr_pos = x;
		}
		x++;
	}
	return (NULL);
}
