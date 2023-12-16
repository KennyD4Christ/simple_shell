#include "shell.h"

/**
 **stringncpy - copies a string
 *@destination: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *stringncpy(char *destination, char *src, int n)
{
	int x, y;
	char *s = destination;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		destination[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			destination[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
 **stringncat - concatenates two strings
 *@destination: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *stringncat(char *destination, char *src, int n)
{
	int x, y;
	char *s = destination;

	x = 0;
	y = 0;
	while (destination[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		destination[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		destination[x] = '\0';
	return (s);
}

/**
 **stringchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *stringchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
