#ifndef FUNCTION_POINTERS_H
#define FUNCTION_POINTERS_H

#include <stddef.h>

int _putchar(char c);

/**
 * print_name - prints a name using a callback
 * @name: pointer to the name string
 * @f: function pointer that takes (char *) and returns void
 */
void print_name(char *name, void (*f)(char *));

/**
 * array_iterator - applies an action to each element of an int array
 * @array: pointer to the first element
 * @size: number of elements
 * @action: function pointer that takes an int and returns void
 */
void array_iterator(int *array, size_t size, void (*action)(int));

#endif /* FUNCTION_POINTERS_H */
