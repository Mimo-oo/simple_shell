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

