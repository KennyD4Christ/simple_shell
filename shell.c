#include "shell.h"
#include "alias.h"
/**
 *  * custom_strlen - Custom implementation of strlen
 *   * @str: The input string
 *    * Return: The length of the string
 */
size_t custom_strlen(const char *str)
{
size_t length = 0;
while (str[length] != '\0')
{
length++;
}
return (length);
}
/**
 *  * execute_file_commands - Execute commands from a file
 *   * @filename: The name of the file containing commands
 */
void execute_file_commands(const char *filename)
{
char *line = NULL;
size_t line_len;
int file = open(filename, O_RDONLY);
if (file == -1)
{
perror("execute_file_commands");
_exit(EXIT_FAILURE);
}
while ((line = custom_getline()) != NULL)
{
free(line);
line_len = custom_strlen(line);
if (line_len > 0 && line[line_len - 1] == '\n')
{
line[line_len - 1] = '\0';
}
execute_command(line);
free(line);
line = NULL;
}
free(line);
close(file);
}
/**
 *  * main - The main function
 *   * @argc: The number of command-line arguments
 *    * @argv: The array of command-line arguments
 *     * Return: Always 0
 */
int main(int argc, char *argv[])
{
char *line = NULL;
int read_chars;
char *setenv_test[] = {"setenv", "USERNAME", "test_value", NULL};
handle_setenv(setenv_test);
write(STDOUT_FILENO, "($) ", 4);
if (argc == 2)
{
execute_file_commands(argv[1]);
_exit(0);
}
while ((line = custom_getline()) != NULL)
{
read_chars = custom_strlen(line);
if (read_chars > 0 && line[read_chars - 1] == '\n')
{
line[read_chars - 1] = '\0';
}
if (custom_strlen(line) == 0)
{
continue;
}
execute_command(line);
fflush(stdout);
write(STDOUT_FILENO, "($) ", 4);
}
free(line);
return (0);
}
