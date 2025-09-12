#include "main.h"

/**
 * _strspn - returns the length of the initial segment of @s
 *           consisting only of bytes from @accept
 * @s:       input string (scan starts from its beginning)
 * @accept:  set of allowed bytes
 *
 * Return: number of bytes from the start of @s that are in @accept
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int count = 0;
	int i;

	while (s[count] != '\0')
	{
		for (i = 0; accept[i] != '\0' && accept[i] != s[count]; i++)
			;

		if (accept[i] == '\0')
			break;

		count++;
	}

	return (count);
}
