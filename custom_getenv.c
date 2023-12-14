#include "shell.h"
/**
 *  * custom_strncmp - Compare at most n characters of two strings.
 *   * @s1: The first string to be compared.
 *    * @s2: The second string to be compared.
 *     * @n: The maximum number of characters to compare.
 *      *
 * Return: 0 if the strings are equal, a negative value if s1 is less than s2,
 *        *         or a positive value if s1 is greater than s2.
 */
int custom_strncmp(const char *s1, const char *s2, size_t n)
{
while (n > 0 && *s1 && *s2 && (*s1 == *s2))
{
++s1;
++s2;
--n;
}
if (n == 0)
{
return (0);
}
return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 *  * custom_getenv - Get the value of an environment variable.
 *   * @name: The name of the environment variable.
* Returns a pointer to the value of the environment variable or
*NULL if the environment variable is not found.
**/
char *custom_getenv(const char *name)
{
char **env;
size_t name_len = custom_strlen(name);
for (env = environ; *env != NULL; env++)
{
if (custom_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
{
return (&((*env)[name_len + 1]));
}
}
return (NULL);
}
