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

/**
 * convert_numbers - converter function, a clone of atoi
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_numbers(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removes_comment - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void removes_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

