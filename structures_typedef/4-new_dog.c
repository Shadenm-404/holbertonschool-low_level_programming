#include "dog.h"
#include <stdlib.h>

/**
 * _strlen - returns the length of a string
 * @s: string
 *
 * Return: length (0 if s is NULL)
 */
static int _strlen(char *s)
{
	int l = 0;

	if (s == 0)
		return (0);
	while (s[l] != '\0')
		l++;
	return (l);
}

/**
 * _strcpy - copies src into dest (including '\0')
 * @dest: destination buffer
 * @src: source string
 *
 * Return: dest
 */
static char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (src == 0)
	{
		dest[0] = '\0';
		return (dest);
	}
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * new_dog - creates a new dog and copies name/owner
 * @name: dog's name (must not be NULL)
 * @age: dog's age
 * @owner: owner's name (must not be NULL)
 *
 * Return: pointer to new dog_t on success, or NULL on failure
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *d;
	int ln, lo;

	if (name == 0 || owner == 0)
		return (0);

	d = (dog_t *)malloc(sizeof(*d));
	if (d == 0)
		return (0);

	ln = _strlen(name);
	lo = _strlen(owner);

	d->name = (char *)malloc(ln + 1);
	if (d->name == 0)
	{
		free(d);
		return (0);
	}

	d->owner = (char *)malloc(lo + 1);
	if (d->owner == 0)
	{
		free(d->name);
		free(d);
		return (0);
	}

	_strcpy(d->name, name);
	_strcpy(d->owner, owner);
	d->age = age;

	return (d);
}
