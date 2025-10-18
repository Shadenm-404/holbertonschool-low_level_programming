#include <stdlib.h>
#include "lists.h"

/**
 * insert_dnodeint_at_index - inserts a new node at a given position
 * @h: address of the pointer to the head of the list
 * @idx: index where the new node should be added (starts at 0)
 * @n: integer value to store in the new node
 *
 * Return: address of the new node, or NULL if it failed
 */
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *tmp, *node;
	unsigned int i = 0;

	if (h == NULL)
		return (NULL);

	/* insert at head */
	if (idx == 0)
		return (add_dnodeint(h, n));

	/* walk to the node just before the insertion point (idx - 1) */
	tmp = *h;
	while (tmp != NULL && i < (idx - 1))
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp == NULL)
		return (NULL);

	/* if we are inserting exactly at the end */
	if (tmp->next == NULL)
		return (add_dnodeint_end(h, n));

	/* insert in the middle between tmp and tmp->next */
	node = malloc(sizeof(dlistint_t));
	if (node == NULL)
		return (NULL);

	node->n = n;
	node->prev = tmp;
	node->next = tmp->next;
	tmp->next->prev = node;
	tmp->next = node;

	return (node);
}
