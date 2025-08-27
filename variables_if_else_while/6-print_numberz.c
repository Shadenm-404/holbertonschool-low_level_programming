#include <stdio.h>

/**
 * main - Prints digits 0..9 using putchar
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int i;

	for (i = 0; i <= 9; i++)
	{
		/* use int; no char vars */
		putchar('0' + i);
	}
	putchar('\n');

	return (0);
}
