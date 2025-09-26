#include <stdio.h>
#include "variadic_functions.h"

/**
 * print_numbers - prints numbers separated by a string, then newline
 * @separator: string printed between numbers (ignored if NULL)
 * @n: number of integers passed
 *
 * Return: void
 */
void print_numbers(const char *separator, const unsigned int n, ...)
{
	va_list ap;
	unsigned int i;

	va_start(ap, n);
	for (i = 0; i < n; i++)
	{
		int value = va_arg(ap, int);

		printf("%d", value);
		if (separator && i != n - 1)
			printf("%s", separator);
	}
	printf("\n");
	va_end(ap);
}
