#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 *  *  * execute_script - Execute a script using /bin/bash.
 *   *   * @script_args: Array of script arguments.
 *    *    *
 *     *     * This function uses execve to execute a script using /bin/bash.
 *      *      * It is called when the shebang line indicates a bash script.
 */

void execute_script(char **script_args)
{
execve("/bin/bash", script_args, environ);
perror("execve");
_exit(EXIT_FAILURE);
}
