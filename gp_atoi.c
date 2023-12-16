#include "shell.h"

/**
 * interactive_mode - returns true if shell is interactive mode
 * @shell_info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive_mode(shell_info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->readfd <= 2);
}

/**
 * is_delimiter - checks if character is a delimeter
 * @letter: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char letter, char *delim)
{
	while (*delim)
		if (*delim++ == letter)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@letter: The character to input
 *Return: 1 if letter is alphabetic, 0 otherwise
 */

int _isalpha(int letter)
{
	if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int x, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (x = 0;  s[x] != '\0' && flag != 2; x++)
	{
		if (s[x] == '-')
			sign *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
