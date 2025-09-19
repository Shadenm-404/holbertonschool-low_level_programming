#include "dog.h"
#include <stdlib.h>

/**
 * free_dog - frees a dog_t and its dynamic members
 * @d: pointer to dog to free
 */
void free_dog(dog_t *d)
{
	if (d == 0)
		return;

	free(d->name);
	free(d->owner);
	free(d);
}

