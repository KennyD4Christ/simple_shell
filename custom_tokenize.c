#include "shell.h"
/**
 *  * custom_strdup - Duplicate a string
 *   * @str: The string to duplicate
 *    *
 *     * Return: A newly allocated string containing the duplicated string
 */
char *custom_strdup(const char *str)
{
size_t i;
char *duplicate;
size_t length = 0;
const char *current = str;
while (*current != '\0')
{
length++;
current++;
}
duplicate = malloc((length + 1) * sizeof(char));
if (duplicate == NULL)
{
perror("custom_strdup");
exit(EXIT_FAILURE);
}
for (i = 0; i < length; i++)
{
duplicate[i] = str[i];
}
duplicate[length] = '\0';
return (duplicate);
}

/**
 *  * custom_tokenize - Tokenize a string based on space characters
 *   * @input: The input string to tokenize
 *    *
 * Return: An array of strings (tokens). The last element is NULL.
 */
char **custom_tokenize(char *input)
{
char *token_start;
char *token_end;
const char *delimiters = " \t\n";
char **tokens = NULL;
size_t token_count = 0;
size_t max_tokens = 10;
tokens = malloc(max_tokens * sizeof(char *));
if (tokens == NULL)
{
perror("custom_tokenize");
exit(EXIT_FAILURE);
}
token_start = input;
token_end = input;
while (*token_end != '\0')
{
while (*token_start != '\0' && is_delimiter(*token_start, delimiters))
token_start++;
token_end = token_start;
while (*token_end != '\0' && !is_delimiter(*token_end, delimiters))
token_end++;
if (token_start != token_end)
{
tokens[token_count] = custom_strdup(token_start);
token_count++;
if (token_count >= max_tokens - 1)
{
max_tokens *= 2;
tokens = custom_realloc(tokens, max_tokens *sizeof(char *));
if (tokens == NULL)
{
perror("custom_tokenize");
exit(EXIT_FAILURE);
}
}
}
token_start = token_end + 1;
}
tokens[token_count] = NULL;
return (tokens);
}
/**
 *  * is_delimiter - Check if a character is a delimiter
 *   * @c: The character to check
 *    * @delimiters: The string containing delimiters
 *     *
 *      * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delimiter(char c, const char *delimiters)
{
while (*delimiters != '\0')
{
if (*delimiters == c)
return (1);
delimiters++;
}
return (0);
}

/**
 *  * custom_realloc - Resize a memory block
 *   * @ptr: Pointer to the memory block to resize
 *    * @size: New size of the memory block
 *     *
 *      * Return: Pointer to the resized memory block
 */
void *custom_realloc(void *ptr, size_t size)
{
void *new_ptr = malloc(size);
if (new_ptr == NULL)
{
perror("custom_realloc");
exit(EXIT_FAILURE);
}
free(ptr);
return (new_ptr);
}
