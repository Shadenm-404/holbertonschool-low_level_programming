#include "main.h"

/**
 * _strncat - concatenates two strings using at most n bytes of src
 * @dest: destination buffer (must have enough space)
 * @src: source string
 * @n: maximum number of bytes to copy from src
 *
 * Description: Appends at most @n bytes from @src to the end of @dest.
 * If @src is shorter than @n, stops at its null byte. Always terminates
 * @dest with '\0'. Returns @dest.
 * Return: pointer to dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int j = 0;

	if (!dest || !src || n <= 0)
		return (dest);

	while (dest[i] != '\0')
		i++;

	while (j < n && src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}

	dest[i + j] = '\0';
	return (dest);
}
