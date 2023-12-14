#include <unistd.h>
#include "shell.h"

/**
 *  * execute_env_command - Execute the 'env' command
 */
void execute_env_command(void)
{
char **env;
size_t len;
for (env = environ; *env != NULL; env++)
{
len = custom_strlen(*env);
write(STDOUT_FILENO, *env, len);
write(STDOUT_FILENO, "\n", 1);
}
}

/**
 *  * execute_command - Execute a command
 *   * @command: The command to be executed
 */
void execute_command(char *command)
{
size_t i, j, k;
char **commands = split_line(expand_variables(command), ";");
for (i = 0; commands[i] != NULL; i++)
{
char **and_commands = split_line(expand_variables(commands[i]), "&&");
for (j = 0; and_commands[j] != NULL; j++)
{
char **or_commands = split_line(expand_variables(and_commands[j]), "||");
int or_result = 0;
for (k = 0; or_commands[k] != NULL; k++)
{
char *expanded_command = expand_variables(or_commands[k]);
char **args = split_line(expanded_command, " ");
if (custom_strcmp(args[0], "env") == 0)
{
execute_env_command();
}
else
{
if (handle_builtin_commands(args))
continue;
if (execute_external_command(args))
or_result = 1;
free(args);
}
free(expanded_command);
}
free(or_commands);
if (or_result && and_commands[j + 1] != NULL)
continue;
}
free(and_commands);
}
free(commands);
}
