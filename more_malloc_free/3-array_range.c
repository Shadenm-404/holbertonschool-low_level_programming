#include "main.h"

/**
 * array_range - creates an array of ints from min to max (inclusive)
 * @min: starting value (included)
 * @max: ending value (included)
 *
 * Return: pointer to newly allocated array ordered from min to max,
 *		or NULL if min > max or if allocation fails.
 */
int *array_range(int min, int max)
{
	unsigned int len, i;
	int *arr;

	if (min > max)
		return (NULL);

	len = (unsigned int)(max - min + 1);

	arr = (int *)malloc(len * sizeof(int));
	if (arr == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		arr[i] = min + (int)i;

	return (arr);
}
