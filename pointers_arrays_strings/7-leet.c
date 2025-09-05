#include "main.h"

/**
 * leet - encodes a string into 1337
 * @s: pointer to the string to modify
 *
 * Maps: a/A->4, e/E->3, o/O->0, t/T->7, l/L->1.
 * Two loops total: table init + walk over the string.
 * Return: pointer to the modified string
 */
char *leet(char *s)
{
	int i = 0, k;
	unsigned char uc;
	char map[256];

	/* init lookup table to identity */
	for (k = 0; k < 256; k++)
		map[k] = (char)k;

	/* set leet mappings */
	map[(unsigned char) 'a'] = '4';
	map[(unsigned char) 'A'] = '4';
	map[(unsigned char) 'e'] = '3';
	map[(unsigned char) 'E'] = '3';
	map[(unsigned char) 'o'] = '0';
	map[(unsigned char) 'O'] = '0';
	map[(unsigned char) 't'] = '7';
	map[(unsigned char) 'T'] = '7';
	map[(unsigned char) 'l'] = '1';
	map[(unsigned char) 'L'] = '1';

	/* walk the string; no if needed */
	while (s && s[i] != '\0')
	{
		uc = (unsigned char) s[i];
		s[i] = map[uc];
		i++;
	}
	return (s);
}
