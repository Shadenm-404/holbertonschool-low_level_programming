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

/* Task 1 prototype */
void init_dog(struct dog *d, char *name, float age, char *owner);

#endif /* DOG_H */
void print_dog(struct dog *d);
