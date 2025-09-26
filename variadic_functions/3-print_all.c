#include <stdio.h>
#include <stdarg.h>
#include "variadic_functions.h"

/**
 * print_all - prints anything based on a format string
 * @format: list of types: 'c' char, 'i' int, 'f' float, 's' string
 *
 * Notes:
 * - other chars are ignored
 * - NULL string prints as "(nil)"
 * - no for/goto/else/?:/do-while; <= 2 while; <= 9 vars
 */
void print_all(const char * const format, ...)
{
	va_list ap;
	unsigned int i = 0;
	char *s;
	char *sep = "";

	va_start(ap, format);

	while (format && format[i])
	{
		switch (format[i])
		{
		case 'c':
			printf("%s%c", sep, (char)va_arg(ap, int));
			sep = ", ";
			break;
		case 'i':
			printf("%s%d", sep, va_arg(ap, int));
			sep = ", ";
			break;
		case 'f':
			printf("%s%f", sep, va_arg(ap, double));
			sep = ", ";
			break;
		case 's':
			s = va_arg(ap, char *);
			if (s == NULL)
				s = "(nil)";
			printf("%s%s", sep, s);
			sep = ", ";
			break;
		default:
			break;
		}
		i++;
	}

	printf("\n");
	va_end(ap);
}
