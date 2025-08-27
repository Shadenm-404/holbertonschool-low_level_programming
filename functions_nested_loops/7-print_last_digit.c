#include "main.h"
int print_last_digit(int n)
{
	int d = n % 10;
	if (d < 0)
	d = -d;
	_putchar('0' + d);
	return (d);
}
