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

