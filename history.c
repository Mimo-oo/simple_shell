/**
 * g_history_file - gets the history files
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */

char *g_history_file(info_m *info)
{
	char *buf, *dir;

	dir = _getdenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_m *info)
{
	ssize_t fd;
	char *filename = g_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfdesc(node->str, fd);
		_putfdesc('\n', fd);
	}
	_putfdesc(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

