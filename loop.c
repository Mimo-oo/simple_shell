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

