#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @shell_info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(shell_info_t *shell_info, char **buf, size_t *len)
{
	ssize_t b = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)shell_info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, Handler);
#if USE_GL
		b = getline(buf, &len_p, stdin);
#else
		b = get_line(shell_info, buf, &len_p);
#endif
		if (b > 0)
		{
			if ((*buf)[b - 1] == '\n')
			{
				(*buf)[b - 1] = '\0'; /* remove trailing newline */
				b--;
			}
			shell_info->linecount_flag = 1;
			rm_coms(*buf);
			b_hist_list(shell_info, *buf, shell_info->histcount++);
			/* if (stringchr(*buf, ';')) is this a command chain? */
			{
				*len = b;
				shell_info->cmd_buf = buf;
			}
		}
	}
	return (b);
}

/**
 * get_kmd - gets a line minus the newline
 * @shell_info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_kmd(shell_info_t *shell_info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t x, y, len;
	ssize_t b = 0;
	char **buf_p = &(shell_info->arg), *p;

	_putchar(BUF_FLU);
	b = input_buf(shell_info, &buf, &len);
	if (b == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		y = x; /* init new iterator to current buf position */
		p = buf + x; /* get pointer for return */

		check_rope(shell_info, buf, &y, x, len);
		while (y < len) /* iterate to semicolon or end */
		{
			if (is_rope(shell_info, buf, &y))
				break;
			y++;
		}

		x = y + 1; /* increment past nulled ';'' */
		if (x >= len) /* reached end of buffer? */
		{
			x = len = 0; /* reset position and length */
			shell_info->cmd_buf_type = KMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (stringlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from get_line() */
	return (b); /* return length of buffer from get_line() */
}

/**
 * read_buf - reads a buffer
 * @shell_info: parameter struct
 * @buf: buffer
 * @x: size
 *
 * Return: b
 */
ssize_t read_buf(shell_info_t *shell_info, char *buf, size_t *x)
{
	ssize_t b = 0;

	if (*x)
		return (0);
	b = read(shell_info->readfd, buf, RD_BUF_SZ);
	if (b >= 0)
		*x = b;
	return (b);
}

/**
 * get_line - gets the next line of input from STDIN
 * @shell_info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(shell_info_t *shell_info, char **ptr, size_t *length)
{
	static char buf[RD_BUF_SZ];
	static size_t x, len;
	size_t k;
	ssize_t b = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (x == len)
		x = len = 0;

	b = read_buf(shell_info, buf, &len);
	if (b == -1 || (b == 0 && len == 0))
		return (-1);

	c = stringchr(buf + x, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _relock(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		stringncat(new_p, buf + x, k - x);
	else
		stringncpy(new_p, buf + x, k - x + 1);

	s += k - x;
	x = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * Handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLU);
}
