#include "shell.h"

/**
 * _error_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if none of the numbers is string, converted number otherwise
 *       -1 on error
 */
int _error_atoi(char *s)
{
	int i = 0;
	unsigned long int results = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			results *= 10;
			results += (s[i] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estrr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_m *info, char *estrr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_desc(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estrr);
}

/**
 * print_desc - function prints a decimal (integer) number in base 10
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_desc(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, currentone;

	if (fd == STDERR_FILENO)
		__putchar = _dputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	currentone = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + currentone / i);
			count++;
		}
		currentone %= i;
	}
	__putchar('0' + currentone);
	count++;

	return (count);
}

