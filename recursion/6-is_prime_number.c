#include "main.h"

/**
 * _prime_check - recursively checks if @n has any odd divisor >= @d
 * @n: number to test for primality
 * @d: current odd divisor candidate (start from 3, step +2)
 *
 * Return: 1 if no divisor is found (prime), 0 otherwise
 */
int _prime_check(int n, int d)
{
	if (d > n / d)
		return (1);
	if (n % d == 0)
		return (0);
	return (_prime_check(n, d + 2));
}

/**
 * is_prime_number - returns 1 if @n is a prime number, otherwise 0
 * @n: input integer
 *
 * Return: 1 if prime, 0 otherwise
 */
int is_prime_number(int n)
{
	if (n <= 1)
		return (0);
	if (n == 2 || n == 3)
		return (1);
	if (n % 2 == 0)
		return (0);
	return (_prime_check(n, 3));
}
