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

void init_dog(struct dog *d, char *name, float age, char *owner);
void print_dog(struct dog *d);

#endif /* DOG_H */

