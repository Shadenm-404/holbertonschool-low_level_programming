#include "function_pointers.h"
/**
 * int_index - searches for an int using a comparator
 * @array: pointer to first element
 * @size: number of elements in @array
 * @cmp: comparator function, returns non-zero on match
 *
 * Return: index of first match; -1 if no match or invalid args/size.
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (!array || !cmp || size <= 0)
		return (-1);

	for (i = 0; i < size; i++)
	{
		if (cmp(array[i]) != 0)
			return (i);
	}
	return (-1);
}
