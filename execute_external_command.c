#include "shell.h"

/**
 *  *wait_for_child_process - This function waits for the specified
 *   *child process to complete, collecting
 *    *@pid: The process ID of the child process.
 * @status: A pointer to an integer where the termination status is stored.
 */
void wait_for_child_process(pid_t pid, int *status)
{
pid_t wpid;
do {
wpid = waitpid(pid, status, WUNTRACED);
		if (wpid == -1)
		{
			perror("waitpid");
			_exit(EXIT_FAILURE);
		}
	} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
}

/**
 *  * execute_external_command - Execute an external command or script.
 *   * @args: Array of command arguments.
 *    *
 *     * This function forks a child process to execute an external command
 * or script, waits for the child process to complete, and returns the result.
 *       *
 *        * Return: 1 on success, 0 on failure.
 */
int execute_external_command(char **args)
{
int status;
char *full_path;
pid_t pid;
if (args == NULL || args[0] == NULL)
{
write(STDERR_FILENO, "Invalid arguments\n", 18);
return (0);
}
if (is_builtin(args[0]))
{
return (handle_builtin_commands(args));
}
full_path = (custom_strchr(args[0], '/') != NULL) ? custom_strdup(args[0]) :
get_full_path(args[0]);
if (full_path == NULL)
{
write(STDERR_FILENO, "Command not found: ", 20);
write(STDERR_FILENO, args[0], custom_strlen(args[0]));
write(STDERR_FILENO, "\n", 1);
return (0);
}
pid = fork();
if (pid == 0)
{
execute_child_or_script(full_path, args);
}
else if (pid < 0)
{
perror("execute_external_command");
_exit(EXIT_FAILURE);
}
else
{
wait_for_child_process(pid, &status);
free(full_path);
return (WIFEXITED(status) && (WEXITSTATUS(status) == 0));
}
return (0);
}
/**
 *  * execute_child_or_script - Execute child process or
 *  script based on the given path.
 *   * @full_path: Full path to the command or script.
 *    * @args: Array of command arguments.
 */
void execute_child_or_script(const char *full_path, char **args)
{
if (execve(full_path, args, environ) == -1)
{
perror("execute_child_or_script");
_exit(EXIT_FAILURE);
}
}
