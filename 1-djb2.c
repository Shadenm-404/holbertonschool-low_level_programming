#include "hash_tables.h"

/**
 * hash_djb2 - Hash function implementing the djb2 algorithm
 * @str: Pointer to unsigned char string to hash
 *
 * Return: The computed hash as an unsigned long int
 *
 * Description: djb2 by Dan Bernstein.
 * hash = 5381
 * hash = hash * 33 + c
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (hash);
}
