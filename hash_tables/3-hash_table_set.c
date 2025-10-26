#include "hash_tables.h"

/**
 * hash_table_set - Adds or updates a key/value pair in a hash table
 * @ht: Pointer to hash table
 * @key: The key
 * @value: The value to associate with key
 *
 * Return: 1 if success, 0 otherwise
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *node, *tmp;
	char *value_copy;
	unsigned long int index;

	if (ht == NULL || key == NULL || value == NULL || *key == '\0')
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	tmp = ht->array[index];

	while (tmp && strcmp(tmp->key, key) == 0)
	{
		value_copy = strdup(value);
		if (value_copy == NULL)
			return (0);
		free(tmp->value);
		tmp->value = value_copy;
		return (1);
	}

	node = malloc(sizeof(hash_node_t));
	if (node == NULL)
		return (0);

	node->key = strdup(key);
	if (node->key == NULL)
	{
		free(node);
		return (0);
	}

	node->value = strdup(value);
	if (node->value == NULL)
	{
		free(node->key);
		free(node);
		return (0);
	}

	node->next = ht->array[index];
	ht->array[index] = node;

	return (1);
}
