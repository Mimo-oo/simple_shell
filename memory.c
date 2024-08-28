#include "shell.h"

/**
 * b_free - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int b_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

#include "shell.h"

/**
 * i_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int i_cmd(info_m *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, m = 0;

	for (m = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[m++] = pathstr[i];
	buf[m] = 0;
	return (buf);
}

/**
 * finds_path - finds this command in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of command if found or NULL
 */
char *finds_path(info_m *info, char *pathstr, char *cmd)
{
	int i = 0, currt_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (i_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, currt_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (i_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			currt_pos = i;
		}
		i++;
	}
	return (NULL);
}

