#include "shell.h"

/**
 * errputs - prints an input string
 * @strs: the string to be printed
 *
 * Return: Nothing
 */
void errputs(char *strs)
{
	int x = 0;

	if (!strs)
		return;
	while (strs[x] != '\0')
	{
		errputch(strs[x]);
		x++;
	}
}

/**
 * errputch - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int errputch(char c)
{
	static int x;
	static char buf[W_BUF_SZ];

	if (c == BUF_FLU || x >= W_BUF_SZ)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLU)
		buf[x++] = c;
	return (1);
}

/**
 * _putfind - writes the character c to given fd
 * @c: The character to print
 * @find: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfind(char c, int find)
{
	static int x;
	static char buf[W_BUF_SZ];

	if (c == BUF_FLU || x >= W_BUF_SZ)
	{
		write(find, buf, x);
		x = 0;
	}
	if (c != BUF_FLU)
		buf[x++] = c;
	return (1);
}

/**
 *_putsfind - prints an input string
 * @str: the string to be printed
 * @find: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfind(char *str, int find)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _putfind(*str++, find);
	}
	return (x);
}
