#include "shell.h"

/**
 *  *  * custom_itoa - Custom implementation of itoa
 *   *   * @value: The integer value to convert to a string
 * Return: A dynamically allocated string representing the integer value
 */
char *custom_itoa(int value)
{
char *result;
int i;
int num_digits = 1;
int temp = value;
while (temp / 10 != 0)
{
num_digits++;
temp /= 10;
}
result = malloc(num_digits + 1);
if (!result)
{
perror("malloc error");
_exit(EXIT_FAILURE);
}
i = num_digits - 1;
do {
result[i--] = '0' + (value % 10);
value /= 10;
} while (value != 0);
result[num_digits] = '\0';
return (result);
}

/**
 *  * custom_strstr - Custom implementation of strstr
 *   * @haystack: The string to search in
 *    * @needle: The substring to search for
 *     * Return: A pointer to the first occurrence of the substring,
 *     or NULL if not found
 */
char *custom_strstr(const char *haystack, const char *needle)
{
const char *h;
const char *n;
while (*haystack != '\0')
{
h = haystack;
n = needle;
while (*n != '\0' && *h == *n)
{
h++;
n++;
}
if (*n == '\0')
{
return ((char *)haystack);
}
haystack++;
}
return (NULL);
}
/**
 *  * expand_variables - Expand special variables in the command
 *   * @command: The command to be executed
 *    * Return: A dynamically allocated string with expanded variables
 */
char *expand_variables(char *command)
{
char *expanded_command = custom_strdup(command);
char *result;
char *position;
while ((position = custom_strstr(expanded_command, "$?")) != NULL)
{
char exit_status_str[12];
custom_strncpy(exit_status_str, custom_itoa(last_command_exit_status()),
sizeof(exit_status_str));
result = malloc(custom_strlen(expanded_command) - 2 +
custom_strlen(exit_status_str) + 1);
custom_strncpy(result, expanded_command, position - expanded_command);
result[position - expanded_command] = '\0';
custom_strcat(result, exit_status_str);
custom_strcat(result, position + 2);
free(expanded_command);
expanded_command = result;
}
while ((position = custom_strstr(expanded_command, "$$")) != NULL)
{
char process_id_str[12];
custom_strncpy(process_id_str, custom_itoa(getpid()), sizeof(process_id_str));
result = malloc(custom_strlen(expanded_command) - 1 +
custom_strlen(process_id_str) + 1);
custom_strncpy(result, expanded_command, position - expanded_command);
result[position - expanded_command] = '\0';
custom_strcat(result, process_id_str);
custom_strcat(result, position + 2);
free(expanded_command);
expanded_command = result;
}
return (expanded_command);
}
