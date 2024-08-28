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

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_m *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = finds_path(info, _getdenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((in_interactive(info) || _getdenv(info, "PATH=")
			|| info->argv[0][0] == '/') && i_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_m *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: put error function */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			free_infos(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: put error function */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

