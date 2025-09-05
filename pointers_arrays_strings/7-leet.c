#include "main.h"

/**
 * leet - encodes a string into 1337
 * @s: pointer to the string to modify
 *
 * Mapping:
 * a/A->4, e/E->3, o/O->0, t/T->7, l/L->1
 * Return: pointer to the modified string
 */
char *leet(char *s)
{
	int i = 0, j;
	char *letters = "aAeEoOtTlL";
	char *codes =   "4433007711";

	if (!s)
		return (s);

	while (s[i] != '\0')
	{
		for (j = 0; letters[j] != '\0'; j++)
		{
			if (s[i] == letters[j])
			{
				s[i] = codes[j];
				break;
			}
		}
		i++;
	}
	return (s);
}
