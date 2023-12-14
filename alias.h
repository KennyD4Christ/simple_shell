#ifndef ALIAS_H
#define ALIAS_H
/**
 *  *  * struct Alias - Represents an alias in the shell.
 *   *   * @name: The name of the alias.
 *    *    * @value: The value associated with the alias.
 *    @next: Pointer to the next alias in the list
 */
typedef struct Alias
{
char *name;
char *value;
struct Alias *next;
} Alias;
extern Alias *alias_list;
void handle_alias(char **args);
void print_all_aliases(void);
void print_alias(char *name);
void define_alias(char *name, char *value);
Alias *find_alias(char *name);

#endif /* ALIAS_H */
