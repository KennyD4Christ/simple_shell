#include "shell.h"

/**
 *  * custom_strcpy - Custom implementation of strcpy.
 *   * @dest: The destination string.
 *    * @src: The source string.
 */

void custom_strcpy(char *dest, const char *src)
{
while ((*dest++ = *src++))
;
}

/**
 *  * custom_strncpy - Custom implementation of strncpy.
 *   * @dest: The destination string.
 *    * @src: The source string.
 *     * @n: The maximum number of characters to copy.
 */

void custom_strncpy(char *dest, const char *src, size_t n)
{
while (n-- && (*dest++ = *src++))
;
}

/**
 *  * custom_strcmp - Custom implementation of strcmp
 *   * @s1: The first string
 *    * @s2: The second string
 *     * Return: 0 if the strings are equal, a negative value if s1 < s2,
 *      *         or a positive value if s1 > s2
 */

int custom_strcmp(const char *s1, const char *s2)
{
while (*s1 && (*s1 == *s2))
{
s1++;
s2++;
}
return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 *  * is_builtin - Check if a command is a built-in command.
 *   * @command: The command to check.
 *     * Return: 1 if the command is a built-in, 0 otherwise.
 */

int is_builtin(const char *command)
{
int i;
const char *builtins[] = {"exit", "cd", "env", "setenv", "unsetenv", "alias"};
for (i = 0; i < (int)(sizeof(builtins) / sizeof(builtins[0])); i++)
{
if (custom_strcmp(command, builtins[i]) == 0)
{
return (1);
}
}
return (0);
}

/**
 *  * get_full_path - Get the full path of a command using PATH.
 *   * @command: The command to find the full path for.
 *   Return: A pointer to the full path of the command, or NULL if not found.
 */

char *get_full_path(const char *command)
{
int path_found = 0;
char *path_copy;
char *dir;
char *end;
char *full_path;
char *path_env = getenv("PATH");
if (path_env == NULL)
{
perror("getenv");
return (NULL);
}
path_copy = custom_strdup(path_env);
if (path_copy == NULL)
{
perror("custom_strdup");
return (NULL);
}
dir = path_copy;
full_path = NULL;
while (*dir)
{
end = dir;
while (*end && *end != ':')
{
end++;
}
full_path = malloc(end - dir + custom_strlen(command) + 2);
if (full_path == NULL)
{
perror("malloc");
free(path_copy);
return (NULL);
}
custom_strncpy(full_path, dir, end - dir);
full_path[end - dir] = '\0';
custom_strcat(full_path, "/");
custom_strcat(full_path, command);
if (access(full_path, X_OK) == 0)
{
path_found = 1;
break;
}
else
{
free(full_path);
}
dir = (*end) ? end + 1 : end;
}
free(path_copy);
if (path_found)
{
return (full_path);
}
else
{
free(full_path);
return (NULL);
}
}
