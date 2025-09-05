#include "main.h"
#include <stdio.h>

/**
 * print_array - prints n elements of an int array, then newline
 * @a: pointer to the first element of the array
 * @n: number of elements to print
 *
 * Description: Numbers are printed in order, separated by ", "
 * and followed by a newline. If n <= 0, only a newline is printed.
 */
void print_array(int *a, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf("%d", a[i]);
		if (i != n - 1)
			printf(", ");
	}
	printf("\n");
}
