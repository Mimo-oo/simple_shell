#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR	1
#define CMD_AND	2
#define CMDS_CHAIN	3

/* for convert_numbers() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguments to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_m;

#define INFO_INITIALIZE \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_m *);
} builtin_table;


/* for _shloop.c */
int hsh(info_m *, char **);
int find_builtins(info_m *);
void find_cmd(info_m *);
void fork_cmd(info_m *);

/* for _parser.c */
int i_cmd(info_m *, char *);
char *duplicate_chars(char *, int, int);
char *finds_path(info_m *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* for _errors.c */
void _eputs(char *);
int _dputchar(char);
int _putfdesc(char c, int fd);
int _putsfdesc(char *str, int fd);

/* for _string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* for _string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* for _exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* for _tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* for _realloc.c */
char *_memset(char *, char, unsigned int);
void f_free(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* for _memory.c */
int b_free(void **);

/* for _atoi.c */
int in_interactive(info_m *);
int is_delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);

/* for _errors1.c */
int _error_atoi(char *);
void print_error(info_m *, char *);
int print_desc(int, int);
char *convert_numbers(long int, int, int);
void removes_comment(char *);

/* for _builtin.c */
int _exiting(info_m *);
int _chmycd(info_m *);
int _needhelp(info_m *);

/* for _builtin1.c */
int _thehistory (info_m *);
int _myownalias(info_m *);

/*for _getline.c */
ssize_t get_inputs(info_m *);
ssize_t input_buff(info_m *, char **, size_t *);
int _getline(info_m *, char **, size_t *);
void sigint_handler(int);

/* for _getinfo.c */
void clear_infos(info_m *);
void set_infos(info_m *, char **);
void free_infos(info_m *, int);

/* for _environ.c */
char *_getdenv(info_m *, const char *);
int _myenv(info_m *);
int _myownsetenv (info_m *);
int _myownunsetenv (info_m *);
int populates_env_list(info_m *);

/* for _getdenv.c */
char **get_environment(info_m *);
int _unsetenvv(info_m *, char *);
int _setenvir(info_m *, char *, char *);

/* for _history.c */
char *g_history_file(info_m *info);
int write_history(info_m *info);
int rd_history(info_m *info);
int bd_history_list(info_m *info, char *buf, int linecount);
int rnumber_history(info_m *info);

/* for _lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print__list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void frees_list(list_t **);

/* for _lists1.c */
size_t list_lgt(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with_p(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* for _vars.c */
int is_chain(info_m *, char *, size_t *);
void checks_chain(info_m *, char *, size_t *, size_t, size_t);
int replace_alias(info_m *);
int replace_vars(info_m *);
int replaces_strings(char **, char *);

#endif

