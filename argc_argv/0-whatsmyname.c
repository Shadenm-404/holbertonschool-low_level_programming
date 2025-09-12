#include "main.h"
#include <stdio.h>

/**
 * main - prints the program name (including its path), then a new line
 * @argc: number of command-line arguments
 * @argv: array of command-line argument strings
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	(void)argc;
	printf("%s\n", argv[0]);
	return (0);
}
