#include "main.h"

/**
 * puts2 - prints every other character of a string, starting with the first
 *         followed by a new line
 * @str: pointer to the string
 *
 * Description: Prints indices 0, 2, 4, ... until '\0', then prints '\n'.
 */
void puts2(char *str)
{
	int i;

	if (str == 0)
	{
		_putchar('\n');
		return;
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((i % 2) == 0)
			_putchar(str[i]);
	}

	_putchar('\n');
}
