#ifndef FUNCTION_POINTERS_H
#define FUNCTION_POINTERS_H

int _putchar(char c);

/**
 * print_name - prints a name using a callback
 * @name: pointer to the name string
 * @f: function pointer that takes (char *) and returns void
 *
 * Description: If @name or @f is NULL, the function does nothing.
 */
void print_name(char *name, void (*f)(char *));

#endif /* FUNCTION_POINTERS_H */
