#include "shell.h"

/**
 * _thehistory  - displays the history list, one command one each line, starts
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _thehistory(info_m *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_m *info, char *str)
{
	char *h;
	char i;
	int returns;

	h = _strchr(str, '=');
	if (!h)
		return (1);
	i = *h;
	*h = 0;
	returns = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*h = i;
	return (returns);
}

