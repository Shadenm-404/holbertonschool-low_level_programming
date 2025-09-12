#include <stdio.h>

/**
 * is_number - checks if a string contains only digits (non-empty)
 * @s: input string
 * Return: 1 if only digits, 0 otherwise
 */
static int is_number(const char *s)
{
	if (!s || *s == '\0')
		return (0);

	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

/**
 * to_int - converts a non-empty digit-only string to int
 * @s: input string (validated)
 * Return: integer value
 */
static int to_int(const char *s)
{
	int n = 0;

	while (*s)
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n);
}

/**
 * main - adds positive numbers passed as arguments
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error (non-digit symbols)
 */
int main(int argc, char *argv[])
{
	int i, sum = 0;

	if (argc == 1)
	{
		printf("0\n");
		return (0);
	}

	for (i = 1; i < argc; i++)
	{
		if (!is_number(argv[i]))
		{
			printf("Error\n");
			return (1);
		}
		sum += to_int(argv[i]);
	}

	printf("%d\n", sum);
	return (0);
}

