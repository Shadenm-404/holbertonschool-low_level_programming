#include <stdio.h>
#include "dog.h"

/**
 * print_dog - prints a struct dog
 * @d: pointer to struct dog
 *
 * Description: If an element is NULL, prints "(nil)" for it.
 * If d is NULL, prints nothing.
 */
void print_dog(struct dog *d)
{
	if (d == 0)
		return;

	if (d->name != 0)
		printf("Name: %s\n", d->name);
	else
		printf("Name: (nil)\n");

	printf("Age: %f\n", d->age);

	if (d->owner != 0)
		printf("Owner: %s\n", d->owner);
	else
		printf("Owner: (nil)\n");
}

