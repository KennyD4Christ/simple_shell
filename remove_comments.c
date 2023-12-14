#include "shell.h"
#include "alias.h"

/**
 *  * custom_strchr - Custom implementation of strchr
 *   * @s: The string to search in
 *    * @c: The character to search for
 *     * Return: A pointer to the first occurrence of
 *     the character, or NULL if not found
 */
char *custom_strchr(const char *s, int c)
{
while (*s != '\0')
{
if (*s == c)
return ((char *)s);
s++;
}
return (NULL);
}
/**
 *  * remove_comments - Remove comments from a line
 *   * @line: The line to process
 */
void remove_comments(char *line)
{
char *position;
position = custom_strchr(line, '#');
if (position != NULL)
{
*position = '\0';
}
}
