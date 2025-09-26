#ifndef VARIADIC_FUNCTIONS_H
#define VARIADIC_FUNCTIONS_H

#include <stdarg.h>

int _putchar(char c);

/**
 * sum_them_all - returns the sum of all parameters
 * @n: number of variadic integer arguments
 *
 * Return: sum of all arguments, or 0 if @n is 0.
 */
int sum_them_all(const unsigned int n, ...);

#endif /* VARIADIC_FUNCTIONS_H */

void print_numbers(const char *separator, const unsigned int n, ...);
