#include "main.h"
void puts2(char *str)
{
	int i;
	if (str == 0)
	{
		_putchar(n);
		return;
	}
	for (i = 0; str[i] != 0; i++)
		if ((i % 2) == 0)
			_putchar(str[i]);
	_putchar(n);
}
