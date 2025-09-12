#include "main.h"

int _sqrt_helper(int n, int g);

int _sqrt_helper(int n, int g)
{
	if (g > n / g)
		return (-1);
	if (g * g == n)
		return (g);
	return (_sqrt_helper(n, g + 1));
}

int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	return (_sqrt_helper(n, 1));
}
