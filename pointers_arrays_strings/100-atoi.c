#include "main.h"

/**
 * _atoi - convert a string to an integer
 * @s: input string
 *
 * Rules:
 * - Count all '+' and '-' before the first digit
 *   (each '-' flips the sign).
 * - Parse consecutive digits only.
 * - Build the result as negative to avoid overflow.
 * - Return 0 if no digits exist.
 * Return: converted integer
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int result = 0;   /* keep negative while building */
	int started = 0;
	int d;
	int value;

	if (!s)
		return (0);

	/* collect sign from everything before the first digit */
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign = -sign;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			started = 1;
			break;
		}
		/* '+' or any other char is ignored */
		i++;
	}

	if (!started)
		return (0);

	/* read digits; build as negative to avoid overflow */
	while (s[i] >= '0' && s[i] <= '9')
	{
		d = s[i] - '0';
		result = result * 10 - d;
		i++;
	}

	/* final sign */
	value = (sign > 0) ? -result : result;
	return (value);
}
