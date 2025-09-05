#include "main.h"

/**
 * _strcat - concatenates two strings
 * @dest: destination buffer (must have enough space)
 * @src: source string to append
 *
 * Description: Appends @src to @dest, overwriting the '\0' at the end
 * of @dest, then adds a new terminating '\0'. Returns @dest.
 * Return: pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	if (!dest || !src)
		return (dest);

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}

	dest[i + j] = '\0';
	return (dest);
}
