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

