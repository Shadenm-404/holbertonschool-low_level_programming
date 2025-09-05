#include "main.h"

/**
 * _strncpy - copy a string into dest using at most n bytes
 * @dest: destination buffer
 * @src: source string
 * @n: maximum number of bytes to copy
 *
 * Description: Copies up to @n bytes from @src to @dest.
 * If @src is shorter than @n, the remainder is padded with '\0'.
 * If @src has @n or more bytes, no extra '\0' is appended.
 * Return: pointer to dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	if (!dest || !src || n <= 0)
		return (dest);

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}
