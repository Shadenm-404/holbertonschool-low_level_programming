#include "3-calc.h"

/**
 * get_op_func - selects the correct function for an operator
 * @s: operator string
 *
 * Return: pointer to function, or NULL if not found
 *
 * Notes:
 * - only one while and one if here
 * - no switch, for, do, goto, or else
 */
int (*get_op_func(char *s))(int, int)
{
	op_t ops[] = {
		{"+", op_add}, {"-", op_sub}, {"*", op_mul},
		{"/", op_div}, {"%", op_mod}, {0, 0}
	};
	int i = 0;

	while (ops[i].op)
	{
		if (*ops[i].op == *s && s[1] == '\0')
			return (ops[i].f);
		i++;
	}
	return (0);
}
