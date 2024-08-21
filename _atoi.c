#include "shell.h"

/**
 * in_interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if in interactive mode, otherwise 0
 */
int in_interactive(info_m *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if character is a delimeter
 * @c: the char to check
 * @delimit: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char b, char *delimit)
{
	while (*delimit)
		if (*delimit++ == b)
			return (1);
	return (0);
}

