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
	int retrn;

	h = _strchr(str, '=');
	if (!h)
		return (1);
	i = *h;
	*h = 0;
	retrn = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with_p(info->alias, str, -1)));
	*h = i;
	return (retrn);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_m *info, char *str)
{
	char *h;

	h = _strchr(str, '=');
	if (!h)
		return (1);
	if (!*++h)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return:  0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *h = NULL;
	char *c = NULL;

	if (node)
	{
		h = _strchr(node->str, '=');
		for (c = node->str; c <= h; a++)
			_putchar(*c);
		_putchar('\'');
		_puts(h + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myownalias - same as the alias builtin -man alias
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: 0 on success
 */
int _myownalias(info_m *info)
{
	int i = 0;
	char *h = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		h = _strchr(info->argv[i], '=');
		if (h)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with_p(info->alias, info->argv[i], '='));
	}

	return (0);
}

