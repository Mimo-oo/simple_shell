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

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous m-allocate block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: a pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *h;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	h = malloc(new_size);
	if (!h)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		h[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (h);
}

