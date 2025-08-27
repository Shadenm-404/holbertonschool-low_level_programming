#include <stdio.h>

/**
	* main - prints the first 50 Fibonacci numbers starting with 1 and 2
	*
	* Return: Always 0
	*/
int main(void)
{
	unsigned long int a = 1, b = 2, next;
	int i;

	printf("%lu, %lu", a, b);
	for (i = 3; i <= 50; i++)
	{
	next = a + b;
	printf(", %lu", next);
	a = b;
	b = next;
	}
	printf("\n");
	return (0);
}
