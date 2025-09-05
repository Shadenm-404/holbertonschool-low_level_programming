#include "main.h"

/**
 * _atoi - convert a string to an integer
 * @s: input string
 *
 * Description:
 * Scan the string from the start:
 * - For every '-' before the first digit, flip the sign.
 * - '+' is ignored.
 * - When the first digit is reached, parse consecutive digits.
 * - If no digits exist, return 0.
 * Return: the converted integer.
 */
int _atoi(char *s)
{
	int i = 0, sign = 1, started = 0, num = 0;

	if (!s)
		return (0);

	/* accumulate sign from all +/- before first digit */
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] == '+')
			; /* ignore */
		else if (s[i] >= '0' && s[i] <= '9')
		{
			started = 1;
			break;
		}
		i++;
	}

	if (!started)
		return (0);

	/* parse digits */
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 + (s[i] - '0');
		i++;
	}

	return (sign * num);
}
