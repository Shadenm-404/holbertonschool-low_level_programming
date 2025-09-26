#ifndef FUNCTION_POINTERS_H
#define FUNCTION_POINTERS_H

int _putchar(char c);

/**
 * print_name - prints a name using a callback function
 * @name: pointer to char (the name string)
 * @f: pointer to a function that takes (char *) and returns void
 *
 * Description: Caller provides a function (e.g., puts-like) to handle printing.
 */
void print_name(char *name, void (*f)(char *));

#endif /* FUNCTION_POINTERS_H */
