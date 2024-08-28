#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error or error code
 */
int hsh(info_m *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_infos(info);
		if (in_interactive(info))
			_puts("$ ");
		_dputchar(BUFFER_FLUSH);
		r = get_inputs(info);
		if (r != -1)
		{
			set_infos(info, av);
			builtin_ret = find_builtins(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (in_interactive(info))
			_putchar('\n');
		free_infos(info, 0);
	}
	write_history(info);
	free_infos(info, 1);
	if (!in_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtins - finds builtin commands
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtins(info_m *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exiting},
		{"env", _myenv},
		{"help", _needhelp},
		{"history", _thehistory},
		{"setenv", _myownsetenv},
		{"unsetenv", _myownunsetenv},
		{"cd", _chmycd},
		{"alias", _myownalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

