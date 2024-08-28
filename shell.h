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

