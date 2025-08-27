#include <stdio.h>

/**
	* main - prints the sum of even Fibonacci terms not exceeding 4,000,000
	*
	* Return: Always 0
	*/
int main(void)
{
	unsigned long int a = 1, b = 2, sum = 0, next;

	while (a <= 4000000)
	{
	if ((a % 2) == 0)
	sum += a;
	next = a + b;
	a = b;
	b = next;
	}
	printf("%lu\n", sum);
	return (0);
}
