#include "shell.h"

/**
 * get_hist_fl - gets the history file
 * @shell_info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_fl(shell_info_t *shell_info)
{
	char *buf, *directory;

	directory = _getenvi(shell_info, "HOME=");
	if (!directory)
		return (NULL);
	buf = malloc(sizeof(char) * (stringlen(directory) + stringlen(HIST_FL) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	stringcpy(buf, directory);
	stringcat(buf, "/");
	stringcat(buf, HIST_FL);
	return (buf);
}

/**
 * w_hist - creates a file, or appends to an existing file
 * @shell_info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int w_hist(shell_info_t *shell_info)
{
	ssize_t fd;
	char *filename = get_hist_fl(shell_info);
	lister *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = shell_info->history; node; node = node->next)
	{
		_putsfind(node->str, fd);
		_putfind('\n', fd);
	}
	_putfind(BUF_FLU, fd);
	close(fd);
	return (1);
}

/**
 * rd_hist - reads history from file
 * @shell_info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int rd_hist(shell_info_t *shell_info)
{
	int x, last = 0, line_cnt = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_fl(shell_info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			b_hist_list(shell_info, buf + last, line_cnt++);
			last = x + 1;
		}
	if (last != x)
		b_hist_list(shell_info, buf + last, line_cnt++);
	free(buf);
	shell_info->histcount = line_cnt;
	while (shell_info->histcount-- >= HIST_MX)
		delNodeAtIndex(&(shell_info->history), 0);
	renum_hist(shell_info);
	return (shell_info->histcount);
}

/**
 * b_hist_list - adds entry to a history linked list
 * @shell_info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @line_cnt: the history line_cnt, histcount
 *
 * Return: Always 0
 */
int b_hist_list(shell_info_t *shell_info, char *buf, int line_cnt)
{
	lister *node = NULL;

	if (shell_info->history)
		node = shell_info->history;
	addNodeEnd(&node, buf, line_cnt);

	if (!shell_info->history)
		shell_info->history = node;
	return (0);
}

/**
 * renum_hist - renumbers the history linked list after changes
 * @shell_info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_hist(shell_info_t *shell_info)
{
	lister *node = shell_info->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (shell_info->histcount = x);
}
