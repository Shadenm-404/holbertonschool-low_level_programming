#include "main.h"

/**
 * _len - get string length (safe if s is NULL)
 * @s: string
 * Return: length
 */
static unsigned int _len(char *s)
{
	unsigned int l = 0;

	if (!s)
		return (0);
	while (s[l] != '\0')
		l++;
	return (l);
}

/**
 * string_nconcat - concatenates s1 and first n bytes of s2
 * @s1: first string (treat NULL as "")
 * @s2: second string (treat NULL as "")
 * @n: number of bytes from s2 to concatenate
 *
 * Return: pointer to newly allocated string (NULL on failure)
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	unsigned int l1, l2, i, j;
	char *res;

	l1 = _len(s1);
	l2 = _len(s2);
	if (n < l2)
		l2 = n;

	res = (char *)malloc(l1 + l2 + 1);
	if (res == NULL)
		return (NULL);

	/* copy s1 */
	for (i = 0; i < l1; i++)
		res[i] = s1 ? s1[i] : '\0';

	/* append first n bytes (or full s2) */
	for (j = 0; j < l2; j++)
		res[i + j] = s2 ? s2[j] : '\0';

	res[i + j] = '\0';
	return (res);
}
