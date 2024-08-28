#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@h: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *h, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		h[i] = b;
	return (h);
}

/**
 * f_free - frees a string of strings
 * @pp: string of strings
 */
void f_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

