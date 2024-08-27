#include "shell.h"

/**
 * clear_infos - initializes info_m struct
 * @info: struct address
 */
void clear_infos(info_m *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_infos - initializes info_m struct
 * @info: struct address
 * @av: argument vector
 */
void set_infos(info_m *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_infos - frees info_m struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_infos(info_m *info, int all)
{
	f_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		f_free(info->environ);
			info->environ = NULL;
		b_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}
}

