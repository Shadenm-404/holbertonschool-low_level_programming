#include "main.h"

/**
 * _atoi - convert a string to an integer
 * @s: input string
 *
 * Description:
 * - Skips anything until the first digit is found.
 * - Considers all consecutive '+'/'-' signs immediately before the number.
 * - Resets the sign accumulator when a non-sign, non-digit is seen.
 * - Returns 0 if no digits exist in the string.
 * Return: the converted integer
 */
int _atoi(char *s)
{
	int i = 0;
	int sign_acc = 1; /* signs since last non-sign char */
	int sign = 1;
	int started = 0;
	int num = 0;

	if (!s)
		return (0);

	while (s[i] != '\0')
	{
		if (s[i] == '-')
		{
			sign_acc *= -1;
		}
		else if (s[i] == '+')
		{
			/* keep sign_acc as is */
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			sign = sign_acc;
			started = 1;
			break;
		}
		else
		{
			sign_acc = 1; /* reset sign accumulator */
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
