#include <stdlib.h>
#include <string.h>
#include "lists.h"

/**
 * add_node_end - adds a new node at the end of a list_t list
 * @head: address of the pointer to the head of the list
 * @str: string to duplicate into the new node
 *
 * Return: address of the new element, or NULL on failure
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new_node, *temp;
	char *dup;
	unsigned int len = 0;

	if (head == NULL || str == NULL)
		return (NULL);

	dup = strdup(str);
	if (dup == NULL)
		return (NULL);

	while (dup[len] != '\0')
		len++;

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
	{
		free(dup);
		return (NULL);
	}

	new_node->str = dup;
	new_node->len = len;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}

	return (new_node);
}
