#include <stdio.h>

/**
	* main - prints the first 98 Fibonacci numbers starting with 1 and 2
	*
	* Return: Always 0
	*/
int main(void)
{
	unsigned long int a_hi = 0, a_lo = 1;
	unsigned long int b_hi = 0, b_lo = 2;
	unsigned long int n_hi, n_lo, base = 1000000000UL;
	int i;

	printf("%lu, %lu", a_lo, b_lo);

	for (i = 3; i <= 98; i++)
	{
	n_lo = a_lo + b_lo;
	n_hi = a_hi + b_hi + (n_lo / base);
	n_lo %= base;

	if (n_hi)
	printf(", %lu%09lu", n_hi, n_lo);
	else
	printf(", %lu", n_lo);

	a_hi = b_hi; a_lo = b_lo;
	b_hi = n_hi; b_lo = n_lo;
	}

	printf("\n");
	return (0);
}
