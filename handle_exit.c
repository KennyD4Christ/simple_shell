#include "shell.h"
#include "alias.h"
/**
 *  *  * handle_exit - Handle the 'exit' built-in command
 *   *   * @args: The arguments passed to the command
 *     *     * Return: Always returns 0 to indicate that the shell should exit
 */
int handle_exit(char **args)
{
int status = 0;
if (args[1] != NULL)
{
status = atoi(args[1]);
}
set_last_command_exit_status(status);
free(args);
exit(status);
}

/**
 *  *  * handle_env - Handle the 'env' built-in command
 *   *   * @args: The arguments passed to the command
 *     *     * Return: Always returns 1 to indicate success
 */
int handle_env(char **args)
{
int i;
while (environ[i] != NULL)
{
write(STDOUT_FILENO, environ[i], custom_strlen(environ[i]));
write(STDOUT_FILENO, "\n", 1);
i++;
}
free(args);
return (1);
}
