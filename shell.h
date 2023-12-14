#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

extern char **environ;

/* Function prototypes */
char **split_line(char *line, const char *delimiter);
int check_command_exists(const char *command);
int handle_builtin_commands(char **args);
int execute_external_command(char **args);
void remove_comments(char *line);
char **custom_tokenize(char *input);
void execute_file_commands(const char *filename);
void prompt(void);
char *custom_getline(void);
void execute_command(char *command);
char *expand_variables(char *command);
char *read_line(void);
int last_command_exit_status(void);
void set_last_command_exit_status(int status);
int handle_exit(char **args);
int handle_env(char **args);
int handle_setenv(char **args);
int handle_cd(char **args);
int handle_unsetenv(char **args);
void handle_printf(char **args);
int is_builtin(const char *command);
char *get_full_path(const char *command);
char *custom_strdup(const char *str);
void *custom_realloc(void *ptr, size_t size);
int is_delimiter(char c, const char *delimiters);
size_t custom_strlen(const char *str);
int custom_strcmp(const char *s1, const char *s2);
void custom_strcpy(char *dest, const char *src);
void custom_strncpy(char *dest, const char *src, size_t n);
void custom_strcat(char *dest, const char *src);
char *custom_strtok(char *str, const char *delimiters);
char *custom_itoa(int value);
char *custom_strstr(const char *haystack, const char *needle);
void wait_for_child_process(pid_t pid, int *status);
char *custom_strchr(const char *str, int c);
void execute_env_command(void);
int check_newline(char *line, size_t index);
ssize_t read_chunk(char *line, size_t index, size_t bufsize);
void execute_script(char **script_args);
char **prepare_script_args(const char *full_path);
void handle_script(const char *full_path, char **args);
void execute_child_or_script(const char *full_path, char **args);
void setup_environment(int interactive);
char *custom_getenv(const char *name);
int custom_strncmp(const char *s1, const char *s2, size_t n);

#endif /* SHELL_H */
