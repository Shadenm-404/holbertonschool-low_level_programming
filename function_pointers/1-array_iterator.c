#include "function_pointers.h"

/**
 * array_iterator - applies a function to each element of an array
 * @array: pointer to the first int element
 * @size: number of elements in the array
 * @action: function pointer to apply on each element
 *
 * Description: If @array or @action is NULL, the function does nothing.
 * Return: void
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
	size_t i;

	if (!array || !action)
		return;

	for (i = 0; i < size; i++)
		action(array[i]);
}
