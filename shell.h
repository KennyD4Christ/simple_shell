#ifndef _SHELL_H_
#define _SHELL_H_

#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

/* for read/write buffers */
#define RD_BUF_SZ 1024
#define W_BUF_SZ 1024
#define BUF_FLU -1

/* for command chaining */
#define KMD_NORM    0
#define KMD_OR      1
#define KMD_AND     2
#define KMD_ROPE    3

/* for convert_number() */
#define CON_LC      1
#define CON_UNSIGNED    2

/* 1 if using system getline() */
#define USE_GL 0
#define USE_STK 0

#define HIST_FL ".simple_shell_history"
#define HIST_MX 4096

extern char **environ;

/**
 * struct liststring - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststring
{
    int num;
    char *str;
    struct liststring *next;
} lister;

/**
 *struct passInformation - contains pseudo-arguments to pass into a function,
 *      allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@history: the history node
 *@alias: the alias node
 *@environ: custom modified copy of environ from LL env
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: KMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passInformation
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    lister *env;
    lister *history;
    lister *alias;
    char **environ;
    int env_changed;
    int status;

    char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
    int cmd_buf_type; /* KMD_type ||, &&, ; */
    int readfd;
    int histcount;
} shell_info_t;

#define SHELL_INFO_T_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 *struct sys_builtin_tb - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct sys_builtin_tb
{
    char *type;
    int (*func)(shell_info_t *);
} sys_builtin_tb;

/* gp_shell_loop.c */
int hshell(shell_info_t *, char **);
int search_builtin(shell_info_t *);
void search_kmd(shell_info_t *);
void spawn_kmd(shell_info_t *);

/* gp_parser.c */
int is_kmd(shell_info_t *, char *);
char *dup_ch(char *, int, int);
char *search_path(shell_info_t *, char *, char *);

/* gp_loophshell.c */
int iteratehshell(char **);

/*gp_errors.c */
void errputs(char *);
int errputch(char);
int _putfind(char, int);
int _putsfind(char *, int);

/* gp_string.c */
int stringlen(char *);
int stringcmp(char *, char *);
char *begins_with(const char *, const char *);
char *stringcat(char *, char *);
char *stringchr(char *, char);

/* gp_string1.c */
char *stringcpy(char *, char *);
char *stringdup(const char *);
void _puts(char *);
int _putchar(char);
ssize_t read_buf(shell_info_t *, char *, size_t *);

/* gp_exits.c */
char *stringncpy(char *, char *, int);
char *stringncat(char *, char *, int);
char *stringchr(char *, char);

/* gp_tokenizer.c */
char **stringtow(char *, char *);
char **stringtow2(char *, char);

/* gp_realloc.c */
char *_memset(char *, char, unsigned int);
void forkfree(char **);
void *_relock(void *, unsigned int, unsigned int);

/* gp_memory.c */
int buf_free(void **);

/* gp_atoi.c */
int interactive_mode(shell_info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int _atoi(char *);

/* gp_errors1.c */
int _erratoi(char *);
void output_err(shell_info_t *, char *);
int output_d(int, int);
char *con_num(long int, int, int);
void rm_coms(char *);

/* gp_builtin.c */
int _gpexit(shell_info_t *);
int _gpcd(shell_info_t *);
int _gphelp(shell_info_t *);

/* gp_builtin1.c */
int _gphist(shell_info_t *);
int _gpalias(shell_info_t *);
int output_alias(lister *);
int unset_alias(shell_info_t *, char *);
int set_alias(shell_info_t *, char *);

/* gp_getline.c */
ssize_t get_kmd(shell_info_t *);
int get_line(shell_info_t *, char **, size_t *);
void Handler(int);

/* gp_getinfo.c */
void wipe_shell_info(shell_info_t *);
void set_shell_info(shell_info_t *, char **);
void free_shell_info(shell_info_t *, int);

/* gp_environ.c */
char *_getenvi(shell_info_t *, const char *);
int _gpenvi(shell_info_t *);
int _gpsetenvi(shell_info_t *);
int _gpunsetenvi(shell_info_t *);
int fill_envi_list(shell_info_t *);

/* gp_getenv.c */
char **get_envi(shell_info_t *);
int _unsetenvi(shell_info_t *, char *);
int _setenvi(shell_info_t *, char *, char *);

/* gp_history.c */
char *get_hist_fl(shell_info_t *info);
int w_hist(shell_info_t *info);
int rd_hist(shell_info_t *info);
int b_hist_list(shell_info_t *info, char *buf, int linecount);
int renum_hist(shell_info_t *info);

/* gp_lists.c */
lister *addNode(lister **, const char *, int);
lister *addNodeEnd(lister **, const char *, int);
size_t output_list_string(const lister *);
int delNodeAtIndex(lister **, unsigned int);
void freeList(lister **);

/* gp_lists1.c */
size_t list_length(const lister *);
char **list_2_strs(lister *);
size_t output_list(const lister *);
lister *nodeBeginsWith(lister *, char *, char);
ssize_t getNodeIndex(lister *, lister *);

/* gp_vars.c */
int is_rope(shell_info_t *, char *, size_t *);
void check_rope(shell_info_t *, char *, size_t *, size_t, size_t);
int rep_alias(shell_info_t *);
int rep_vars(shell_info_t *);
int rep_str(char **, char *);

#endif
