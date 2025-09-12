#include "main.h"

/**
 * _strpbrk - finds first byte in @s that matches any byte in @accept
 * @s: string to scan
 * @accept: set of bytes to match
 *
 * Return: pointer to first match in @s, or NULL if none
 */
char *_strpbrk(char *s, char *accept)
{
	int i = 0, j;

	while (s[i] != '\0')
	{
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
				return (s + i);
		}
		i++;
	}

	return (0);
}
