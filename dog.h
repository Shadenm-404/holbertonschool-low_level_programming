#ifndef DOG_H
#define DOG_H

/**
 * struct dog - basic dog structure
 * @name: pointer to dog's name
 * @age: dog's age
 * @owner: pointer to owner's name
 */
struct dog
{
	char *name;
	float age;
	char *owner;
};

/**
 * dog_t - typedef for struct dog
 */
typedef struct dog dog_t;

/* Prototypes needed by tasks */
dog_t *new_dog(char *name, float age, char *owner);
void free_dog(dog_t *d);

#endif /* DOG_H */

