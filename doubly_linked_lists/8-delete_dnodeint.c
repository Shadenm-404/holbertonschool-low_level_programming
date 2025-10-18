#include <stdlib.h>
#include "lists.h"

/**
 * delete_dnodeint_at_index - deletes the node at a given index of a dlistint_t
 * @head: address of the pointer to the head of the list
 * @index: index of the node that should be deleted (starts at 0)
 *
 * Return: 1 if it succeeded, -1 if it failed
 */
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	dlistint_t *tmp;
	unsigned int i = 0;

	if (head == NULL || *head == NULL)
		return (-1);

	/* delete head */
	if (index == 0)
	{
		tmp = *head;
		*head = tmp->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		free(tmp);
		return (1);
	}

	tmp = *head;
	while (tmp != NULL && i < index)
	{
		tmp = tmp->next;
		i++;
	}

	if (tmp == NULL)
		return (-1);

	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;

	free(tmp);
	return (1);
}
