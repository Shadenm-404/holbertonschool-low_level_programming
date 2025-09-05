#include "main.h"

/**
 * puts_half - prints the second half of a string
 * @str: pointer to string
 *
 * Description: Prints the second half of a string, then a newline.
 * If length is even, start at len / 2. If length is odd, start at
 * (len - 1) / 2 + 1 to skip the middle character.
 */
void puts_half(char *str)
{
	int len = 0, i, start;

	if (!str)
	{
		_putchar('\n');
		return;
	}

	while (str[len] != '\0')
		len++;

	if (len % 2 == 0)
		start = len / 2;
	else
		start = (len - 1) / 2 + 1;

	for (i = start; i < len; i++)
		_putchar(str[i]);

	_putchar('\n');
}
