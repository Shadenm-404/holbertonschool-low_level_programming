#include "main.h"

/**
 * array_range - creates an array of ints from min to max (inclusive)
 * @min: starting value (included)
 * @max: ending value (included)
 *
 * Return: pointer to newly allocated array ordered from min to max,
 *         or NULL if min > max or if allocation fails.
 */
int *array_range(int min, int max)
{
	unsigned int len, i;
	int *arr;

	if (min > max)
		return (NULL);

	/* length = max - min + 1 (avoid UB with wider arithmetic) */
	len = (unsigned int)((long long)max - (long long)min + 1);

	/* guard against overflow in len * sizeof(int) */
	if ((size_t)len > SIZE_MAX / sizeof(int))
		return (NULL);

	arr = (int *)malloc(len * sizeof(int));
	if (arr == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		arr[i] = min + (int)i;

	return (arr);
}
