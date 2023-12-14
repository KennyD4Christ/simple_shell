#include "shell.h"

#define INITIAL_BUFFER_SIZE 1024
/**
 *  * read_chunk - Read a chunk of characters from standard input
 *   *
 *    * @line: Pointer to the buffer
 *     * @index: Current index in the buffer
 *      * @bufsize: Current buffer size
 *       *
 *        * Return: Number of characters read
 */
ssize_t read_chunk(char *line, size_t index, size_t bufsize)
{
ssize_t read_chars = read(STDIN_FILENO, &line[index], bufsize - index);
if (read_chars == -1)
{
perror("read_chunk");
exit(EXIT_FAILURE);
}
return (read_chars);
}
/**
 *  * check_newline - Check if a newline character is present in the buffer
 *   *
 *    * @line: Pointer to the buffer
 *     * @index: Current index in the buffer
 *      *
 *       * Return: 1 if newline is found, 0 otherwise
 */
int check_newline(char *line, size_t index)
{
size_t i;
for (i = 0; i < index; i++)
{
if (line[i] == '\n')
{
line[i] = '\0';
return (1);
}
}
return (0);
}
/**
 *  *  * custom_getline - Read a line from standard input
 *   *   *
 *    *    * Return: A pointer to the line read from standard input.
 *  NULL is returned if an error occurs or if EOF is reached.
 */
char *custom_getline(void)
{
char *line = NULL;
static size_t bufsize = INITIAL_BUFFER_SIZE;
size_t index = 0;
ssize_t read_chars;
line = malloc(bufsize);
if (line == NULL)
{
perror("custom_getline: Unable to allocate memory");
_exit(EXIT_FAILURE);
}
while (1)
{
read_chars = read(STDIN_FILENO, line + index, bufsize - index);
if (read_chars == -1)
{
perror("custom_getline: Error reading input");
free(line);
_exit(EXIT_FAILURE);
}
if (read_chars == 0)
{
if (index == 0)
{
free(line);
return (NULL);
}
break;
}
index += read_chars;
if (check_newline(line, index))
{
return (line);
}
if (index >= bufsize - 1)
{
bufsize *= 2;
line = custom_realloc(line, bufsize);
if (line == NULL)
{
perror("custom_getline");
exit(EXIT_FAILURE);
}
}
}
return (line);
}
