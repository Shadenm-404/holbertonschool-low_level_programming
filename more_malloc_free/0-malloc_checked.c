#include "main.h"

/**
 * malloc_checked - allocates memory using malloc
 * @b: number of bytes to allocate
 *
 * Description: If malloc fails, terminate the normal process with status 98.
 * Return: pointer to the allocated memory on success
 */
void *malloc_checked(unsigned int b)
{
	void *p;

	p = malloc(b);
	if (p == NULL)
	{
		/* Normal process termination with specific status as required */
		exit(98);
	}
	return (p);
}
