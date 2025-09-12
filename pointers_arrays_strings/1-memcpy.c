#include "main.h"

/**
 * _memcpy - copies n bytes from src to dest (no overlap support)
 * @dest: destination pointer
 * @src:  source pointer
 * @n:    number of bytes to copy
 *
 * Return: pointer to dest
 * Note: Like standard memcpy, behavior is undefined if regions overlap.
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (dest);
}
