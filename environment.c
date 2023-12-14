#include "shell.h"

/**
 *  * setup_environment - Set up environment variables.
 *   * @interactive: 1 if the shell is in interactive mode, 0 otherwise.
 */

void setup_environment(int interactive)
{
int username_len = custom_strlen("USERNAME") + custom_strlen("kenny_d") + 2;
char *username_var = malloc(username_len);
if (username_var == NULL)
{
perror("malloc");
_exit(EXIT_FAILURE);
}
custom_strcpy(username_var, "USERNAME=kenny_d");
environ[0] = username_var;
if (interactive)
{
int prompt_len = custom_strlen("PROMPT") + custom_strlen("Shell > ") + 2;
char *prompt_var = malloc(prompt_len);
if (prompt_var == NULL)
{
perror("malloc");
_exit(EXIT_FAILURE);
}
custom_strcpy(prompt_var, "PROMPT=Shell > ");
environ[1] = prompt_var;
}
}
