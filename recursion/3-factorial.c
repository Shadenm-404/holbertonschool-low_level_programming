#include "main.h"

/**
 * factorial - returns the factorial of a given number (recursive)
 * @n: input integer
 *
 * Return: -1 if n < 0 (error),
 *         1  if n == 0,
 *         otherwise n * factorial(n - 1)
 */
int factorial(int n)
{
	if (n < 0)
		return (-1);
	if (n == 0)
		return (1);

	return (n * factorial(n - 1));
}
