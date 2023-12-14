#include "shell.h"

/**
 * check_command_exists -  This function checks if the specified
 * command is executable in the system's PATH.
 *       * @command: The command to check.
 *Return: Returns 1 if the command exists and
*is executable, and 0 if otherwise.
 */
int check_command_exists(const char *command)
{
if (access(command, X_OK) == 0)
{
return (1);
}
else
{
return (0);
}
}
