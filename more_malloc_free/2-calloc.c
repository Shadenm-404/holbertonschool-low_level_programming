#include "main.h"

/**
 * _memzero - set n bytes of s to 0
 * @s: pointer to memory
 * @n: bytes to zero
 */
static void _memzero(unsigned char *s, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = 0;
}

/**
 * _calloc - allocates memory for an array and sets it to zero
 * @nmemb: number of elements
 * @size: size of each element
 *
 * Return: pointer to allocated zeroed memory, or NULL on failure
 * Notes:
 * - If nmemb or size is 0 -> return NULL (Holberton requirement)
 * - Prevent overflow on nmemb * size
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *p;
	unsigned int total;

	if (nmemb == 0 || size == 0)
		return (NULL);

	/* overflow guard: nmemb * size must fit in unsigned int */
	if (nmemb > UINT_MAX / size)
		return (NULL);

	total = nmemb * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);

	_memzero((unsigned char *)p, total);
	return (p);
}
