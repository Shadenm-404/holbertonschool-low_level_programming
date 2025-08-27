#include <stdio.h>

/**
 * main - Prints all single-digit base-10 numbers starting from 0
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int i;

	for (i = 0; i <= 9; i++)
	{
		/* '0' هو ثابت محرفي نوعه int في C، ولسنا نستخدم متغير char */
	putchar('0' + i);
	}
	putchar('\n');

	return (0);
}
