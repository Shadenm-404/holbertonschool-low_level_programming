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

<<<<<<< HEAD
void init_dog(struct dog *d, char *name, float age, char *owner);
void print_dog(struct dog *d);
=======
/* Prototype for task 4 */
>>>>>>> 74efd2b (structures_typedef: add 4-new_dog.c and update dog.h (dog_t + prototype))
dog_t *new_dog(char *name, float age, char *owner);

#endif /* DOG_H */
void free_dog(dog_t *d);
