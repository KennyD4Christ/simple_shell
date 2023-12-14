#include <stdlib.h>
#include "shell.h"

static int last_exit_status;

/**
 *  * set_last_command_exit_status - Set the exit status of the last command
 *   * @status: The exit status to set
 */
void set_last_command_exit_status(int status)
{
last_exit_status = status;
}

/**
 *  * last_command_exit_status - Get the exit status of the last command
 *   * Return: The exit status of the last command
 */
int last_command_exit_status(void)
{
return (last_exit_status);
}
