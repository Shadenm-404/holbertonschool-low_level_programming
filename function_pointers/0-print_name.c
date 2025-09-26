#include "function_pointers.h"

/**
 * print_name - prints a name via a function pointer callback
 * @name: pointer to the name string
 * @f: function pointer that receives (char *) and returns void
 *
 * Description: If either @name or @f is NULL, the function does nothing.
 * Return: void
 */
void print_name(char *name, void (*f)(char *))
{
	if (name == (void *)0 || f == (void *)0)
		return;

	f(name);
}
