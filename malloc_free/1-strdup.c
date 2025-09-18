#include "main.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 *           containing a copy of the string given as a parameter
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string, or NULL if str is NULL
 *         or if memory allocation fails
 */
char *_strdup(char *str)
{
	char *copy;
	unsigned int i, len;

	if (str == NULL)
		return (NULL);

	len = 0;
	while (str[len] != '\0')
		len++;

	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		copy[i] = str[i];

	copy[len] = '\0';
	return (copy);
}
