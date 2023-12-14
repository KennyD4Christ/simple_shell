#include "shell.h"
#include "alias.h"

/**
 *  * handle_setenv - Handle the 'setenv' built-in command
 *   * @args: The arguments passed to the command
 *     * Return: Always returns 1 to indicate success
 */
int handle_setenv(char **args)
{
const char *err_str;
if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
{
write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
return (1);
}
else
{
if (setenv(args[1], args[2], 1) == -1)
{
err_str = strerror(errno);
write(STDERR_FILENO, "Error setting environment variable ", 35);
write(STDERR_FILENO, args[1], custom_strlen(args[1]));
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, (errno == EEXIST) ? "Variable already exists" :
err_str, custom_strlen(err_str));
write(STDERR_FILENO, "\n", 1);
}
}
return (1);
}
/**
 *  * handle_cd - Handle the 'cd' built-in command
 *   * @args: The arguments passed to the command
 *     * Return: Always returns 1 to indicate success
 */
int handle_cd(char **args)
{
const char *home_dir = custom_getenv("HOME");
const char *old_pwd = custom_getenv("OLDPWD");
if (args[1] == NULL || args[1][0] == '\0')
{
if (home_dir == NULL)
write(STDERR_FILENO, "cd: HOME not set\n", 17);
else
{
if (chdir(home_dir) != 0)
perror("cd");
}
}
else if (custom_strcmp(args[1], "-") == 0)
{
if (old_pwd == NULL)
write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
else
{
if (chdir(old_pwd) != 0)
perror("cd");
}
}
else
{
if (chdir(args[1]) != 0)
perror("cd");
}
return (1);
}

/**
 *  * handle_unsetenv - Handle the 'unsetenv' built-in command
 *   * @args: The arguments passed to the command
 *     * Return: Always returns 1 to indicate success
 */
int handle_unsetenv(char **args)
{
if (args[1] == NULL)
{
write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
}
else
{
unsetenv(args[1]);
}
free(args);
return (1);
}

/**
 *  * handle_builtin_commands - Execute built-in commands
 *   * @args: The arguments of the command
 *     * Return: 1 if the command was handled, 0 otherwise
 */
int handle_builtin_commands(char **args)
{
if (args[0] != NULL)
{
if (custom_strcmp(args[0], "exit") == 0)
{
handle_exit(args);
return (1);
}
else if (custom_strcmp(args[0], "env") == 0)
{
handle_env(args);
return (1);
}
else if (custom_strcmp(args[0], "setenv") == 0)
{
return (handle_setenv(args));
}
else if (custom_strcmp(args[0], "unsetenv") == 0)
{
return (handle_unsetenv(args));
}
else if (custom_strcmp(args[0], "cd") == 0)
{
return (handle_cd(args));
}
else if (custom_strcmp(args[0], "alias") == 0)
{
handle_alias(args);
return (1);
}
else if (custom_strcmp(args[0], "printf") == 0)
{
handle_printf(args);
return (1);
}
}
return (0);
}
/**
 *  * handle_printf - Custom implementation of printf
 *   * @args: The arguments of the command
 */
void handle_printf(char **args)
{
int i;
for (i = 1; args[i] != NULL; i++)
{
if (i > 1)
write(STDOUT_FILENO, " ", 1);
write(STDOUT_FILENO, args[i], custom_strlen(args[i]));
}
write(STDOUT_FILENO, "\n", 1);
}
