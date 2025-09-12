#include "main.h"

/**
 * _sqrt_helper - helper to find a natural square root recursively
 * @n: the number to get the square root of
 * @g: current guess to test (starting from 1 and increasing)
 *
 * Return: the natural square root if found,
 *         -1 if no natural square root exists for @n
 */
int _sqrt_helper(int n, int g)
{
	if (g > n / g)
		return (-1);
	if (g * g == n)
		return (g);
	return (_sqrt_helper(n, g + 1));
}

/**
 * _sqrt_recursion - returns the natural square root of a number
 * @n: input integer
 *
 * Return: the natural square root of @n,
 *         or -1 if @n is negative or has no natural square root
 */
int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	return (_sqrt_helper(n, 1));
}
