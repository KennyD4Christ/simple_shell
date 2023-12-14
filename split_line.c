#include "shell.h"

#define MAX_TOKENS 64

/**
 *  * split_line - Split a line into tokens
 *   * @line: The input line to be split
 *    * @delimiter: The delimiter used for splitting
 *     *
 *      * Return: An array of tokens
 */
char **split_line(char *line, const char *delimiter)
{
char *start;
size_t token_length;
int i = 0;
char **tokens;
tokens = malloc(sizeof(char *) * (MAX_TOKENS + 1));
if (!tokens)
{
perror("malloc error");
_exit(EXIT_FAILURE);
}
while (*line != '\0')
{
while (*line != '\0' && custom_strchr(delimiter, *line))
line++;
if (*line == '\0')
break;
start = line;
while (*line != '\0' && !custom_strchr(delimiter, *line))
line++;
token_length = line - start;
tokens[i] = malloc(token_length + 1);
if (!tokens[i])
{
perror("malloc error");
_exit(EXIT_FAILURE);
}
custom_strncpy(tokens[i], start, token_length);
tokens[i][token_length] = '\0';
i++;
if (i >= MAX_TOKENS)
{
write(STDERR_FILENO, "Too many tokens. Increase MAX_TOKENS.\n", 37);
exit(EXIT_FAILURE);
}
}
tokens[i] = NULL;
return (tokens);
}
