#include <stddef.h>
#include "main.h"

/**
 * _strchr - locates the first occurrence of a character in a string
 * @s: string to scan
 * @c: character to find
 *
 * Return: pointer to first matching character in @s, or NULL if not found
 *         (if @c is '\0', returns pointer to the terminating null byte)
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}

	if (c == '\0')
		return (s + i);

	return (NULL);
}
