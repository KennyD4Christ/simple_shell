#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

/**
 *  * handle_script - Handle the execution of a script.
 *   * @full_path: Full path to the script.
 *    * @args: Array of script arguments.
 *     *
 * This function reads the shebang line of the script,
 * determines the script type,
 * and executes it accordingly using execute_script or execute_child_process.
 */

void handle_script(const char *full_path, char **args)
{
char **script_args;
char shebang[3];
int script_fd;
(void)args;
script_fd = open(full_path, O_RDONLY);
if (script_fd == -1 || read(script_fd, shebang, sizeof(shebang) - 1) == -1)
{
perror("open");
_exit(EXIT_FAILURE);
}
shebang[sizeof(shebang) - 1] = '\0';
if (custom_strcmp(shebang, "#!") == 0)
{
script_args = malloc(3 * sizeof(char *));
if (!script_args)
{
perror("malloc");
_exit(EXIT_FAILURE);
}
script_args[0] = "/bin/bash";
script_args[1] = custom_strdup(full_path);
script_args[2] = NULL;
execve("/bin/bash", script_args, environ);
perror("execve");
_exit(EXIT_FAILURE);
}
}

/**
 *  * prepare_script_args - Prepare arguments for executing a script.
 *   * @full_path: Full path to the script.
 *    *
 *     * This function prepares the arguments for executing a script,
 *      * including the interpreter path and the script path.
 *       *
 *        * Return: Array of script arguments.
 */

char **prepare_script_args(const char *full_path)
{
char **script_args;
script_args = malloc(3 * sizeof(char *));
if (!script_args)
{
perror("malloc");
_exit(EXIT_FAILURE);
}
script_args[0] = "/bin/bash";
script_args[1] = (char *)full_path;
script_args[2] = NULL;
return (script_args);
}
