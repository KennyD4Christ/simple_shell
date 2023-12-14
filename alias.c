#include "alias.h"
#include "shell.h"

/**
 *  * handle_alias - Handle the alias builtin command
 *   * @args: The arguments passed to the alias command
 */

void handle_alias(char **args)
{
size_t i;
if (args[1] == NULL)
{
print_all_aliases();
}
else
{
for (i = 1; args[i] != NULL; i++)
{
char **alias_parts = split_line(args[i], "=");
if (alias_parts[1] == NULL)
{
print_alias(alias_parts[0]);
}
else
{
define_alias(alias_parts[0], alias_parts[1]);
}
free(alias_parts);
}
}
}

/**
 *  * print_all_aliases - Print all aliases
 */

void print_all_aliases(void)
{
Alias *alias_list = NULL;
Alias *current = alias_list;
while (current != NULL)
{
write(STDOUT_FILENO, current->name, custom_strlen(current->name));
write(STDOUT_FILENO, "='", 2);
write(STDOUT_FILENO, current->value, custom_strlen(current->value));
write(STDOUT_FILENO, "'\n", 2);
current = current->next;
}
}

/**
 *  * print_alias - Print the value of a specific alias
 *   * @name: The name of the alias to print
 */

void print_alias(char *name)
{
Alias *current = find_alias(name);
if (current != NULL)
{
write(STDOUT_FILENO, current->name, custom_strlen(current->name));
write(STDOUT_FILENO, "='", 2);
write(STDOUT_FILENO, current->value, custom_strlen(current->value));
write(STDOUT_FILENO, "'\n", 2);
}
else
{
write(STDERR_FILENO, "alias: ", 7);
write(STDERR_FILENO, name, custom_strlen(name));
write(STDERR_FILENO, ": not found\n", 12);
}
}

/**
 *  * define_alias - Define or redefine an alias
 *   * @name: The name of the alias to define or redefine
 *    * @value: The value of the alias
 */

void define_alias(char *name, char *value)
{
Alias *alias_list = NULL;
Alias *current = find_alias(name);
if (current != NULL)
{
free(current->value);
current->value = custom_strdup(value);
}
else
{
Alias *new_alias = malloc(sizeof(Alias));
new_alias->name = custom_strdup(name);
new_alias->value = custom_strdup(value);
new_alias->next = alias_list;
alias_list = new_alias;
}
}

/**
 *  * find_alias - Find an alias by name
 *   * @name: The name of the alias to find
 *    Return: A pointer to the Alias structure if the alias is found,
 *     or NULL if the alias is not found
 */

Alias *find_alias(char *name)
{
Alias *alias_list = NULL;
Alias *current = alias_list;
while (current != NULL)
{
if (custom_strcmp(current->name, name) == 0)
return (current);
current = current->next;
}
return (NULL);
}
