#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>

/**
 * malloc_checked - allocates memory using malloc; exits with 98 on failure
 * @b: number of bytes to allocate
 *
 * Return: pointer to allocated memory
 */
void *malloc_checked(unsigned int b);

#endif /* MAIN_H */
