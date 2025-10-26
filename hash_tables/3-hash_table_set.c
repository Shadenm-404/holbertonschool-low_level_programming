#include "hash_tables.h"

/**
 * update_value - Updates the value of an existing key
 * @node: Pointer to the hash node
 * @value: New value to assign
 *
 * Return: 1 on success, 0 on failure
 */
int update_value(hash_node_t *node, const char *value)
{
	char *value_copy = strdup(value);

	if (value_copy == NULL)
		return (0);

	free(node->value);
	node->value = value_copy;
	return (1);
}

/**
 * hash_table_set - Adds or updates a key/value pair in a hash table
 * @ht: Pointer to hash table
 * @key: The key string
 * @value: The value string to associate (must be duplicated)
 *
 * Return: 1 on success, 0 on failure
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *node, *tmp;
	char *key_copy, *value_copy;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	tmp = ht->array[index];

	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (update_value(tmp, value));
		tmp = tmp->next;
	}

	node = malloc(sizeof(hash_node_t));
	if (node == NULL)
		return (0);

	key_copy = strdup(key);
	value_copy = strdup(value);
	if (key_copy == NULL || value_copy == NULL)
	{
		free(key_copy);
		free(value_copy);
		free(node);
		return (0);
	}

	node->key = key_copy;
	node->value = value_copy;
	node->next = ht->array[index];
	ht->array[index] = node;

	return (1);
}
