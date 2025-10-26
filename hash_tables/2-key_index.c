#include "hash_tables.h"

/**
 * key_index - Computes the array index for a given key using djb2
 * @key: Key string as unsigned char*
 * @size: Size of the hash table array
 *
 * Return: Index where the key/value should be stored
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int hash;

	if (key == NULL || size == 0)
		return (0);

	hash = hash_djb2(key);
	return (hash % size);
}
