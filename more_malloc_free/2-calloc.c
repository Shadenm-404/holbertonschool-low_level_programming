#include "main.h"

/**
 * _calloc - allocates memory for an array and sets it to zero
 * @nmemb: number of elements
 * @size: size of each element in bytes
 *
 * Return: pointer to allocated zeroed memory, or NULL on failure
 * Notes:
 * - If nmemb == 0 or size == 0 -> return NULL
 * - If nmemb * size overflows -> return NULL
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	unsigned int total, i;
	unsigned char *p;

	if (nmemb == 0 || size == 0)
		return (NULL);

	/* overflow guard */
	if (nmemb > UINT_MAX / size)
		return (NULL);

	total = nmemb * size;

	p = (unsigned char *)malloc(total);
	if (p == NULL)
		return (NULL);

	for (i = 0; i < total; i++)
		p[i] = 0;

	return ((void *)p);
}
