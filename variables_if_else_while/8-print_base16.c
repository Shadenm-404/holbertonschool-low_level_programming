#include <stdio.h>

/**
	* main - Prints all base16 numbers in lowercase
	*
	* Return: Always 0 (Success)
	*/
int main(void)
{
	int ch;

	for (ch = '0'; ch <= '9'; ch++)
	{
	putchar(ch);
	}
	for (ch = 'a'; ch <= 'f'; ch++)
	{
	putchar(ch);
	}
	putchar('\n');

	return (0);
}
