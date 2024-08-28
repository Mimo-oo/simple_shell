#include "shell.h"

/**
 * _exiting - to exit the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototypes.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _exiting(info_m *info)
{
	int checkexit;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		checkexit = _error_atoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_dputchar('\n');
			return (1);
		}
		info->err_num = _error_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _chmycd - changes the current directory 
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _chmycd(info_m *info)
{
	char *d, *dir, buffer[1024];
	int chdir_return;

	d = getcwd(buffer, 1024);
	if (!d)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getdenv(info, "HOME=");
		if (!dir)
			chdir_return = /* TODO: what do you want this to be? */
				chdir((dir = _getdenv(info, "PWD=")) ? dir : "/");
		else
			chdir_return = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getdenv(info, "FMRPWD="))
		{
			_puts(d);
			_putchar('\n');
			return (1);
		}
		_puts(_getdenv(info, "FMRPWD=")), _putchar('\n');
		chdir_return = /* TODO: what should this be? */
			chdir((dir = _getdenv(info, "FMRPWD=")) ? dir : "/");
	}
	else
		chdir_return = chdir(info->argv[1]);
	if (chdir_return == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _dputchar('\n');
	}
	else
	{
		_setenvir(info, "FMRPWD", _getdenv(info, "PWD="));
		_setenvir(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _needhelp - changes the current directory 
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _needhelp(info_m *info)
{
	char **arg_arrays;

	arg_arrays = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arrays); 
	return (0);
}

