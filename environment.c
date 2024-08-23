#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_m *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getdenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getdenv(info_m *info, const char *name)
{
	list_t *node = info->env;
	char *h;

	while (node)
	{
		h = starts_with(node->str, name);
		if (h && *h)
			return (h);
		node = node->next;
	}
	return (NULL);
}

