#include "shell.h"

/**
 * in_interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if in interactive mode, otherwise 0
 */
int in_interactive(info_m *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if character is a delimeter
 * @b: the char to check
 * @delimit: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char b, char *delimit)
{
	while (*delimit)
		if (*delimit++ == b)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabets
 * @d: The character to input
 * Return: 1 if d is an alphabet, otherwise 0
 */

int _isalpha(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, otherwise the converted number
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, out;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		out = -result;
	else
		out = result;

	return (out);
}

