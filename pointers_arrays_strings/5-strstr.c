#include <stddef.h>
#include "main.h"

/**
 * _strstr - finds the first occurrence of the substring @needle in @haystack
 * @haystack: the string to scan
 * @needle:   the substring to find
 *
 * Return: pointer to the beginning of the located substring,
 *         or NULL if the substring is not found.
 *         If @needle is an empty string, returns @haystack.
 */
char *_strstr(char *haystack, char *needle)
{
	int i = 0, j;

	if (needle[0] == '\0')
		return (haystack);

	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			for (j = 0; needle[j] != '\0' && haystack[i + j] == needle[j]; j++)
				;

			if (needle[j] == '\0')
				return (haystack + i);
		}
		i++;
	}

	return (NULL);
}
