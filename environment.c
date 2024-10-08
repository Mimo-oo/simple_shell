#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_m *info)
{
	print__list_str(info->env);
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

/**
 * _myownsetenv  - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myownsetenv(info_m *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenvir(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myownunsetenv  - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myownunsetenv(info_m *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenvv(info, info->argv[i]);

	return (0);
}

/**
 * populates_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populates_env_list(info_m *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

