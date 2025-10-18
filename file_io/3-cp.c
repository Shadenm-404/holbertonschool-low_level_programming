#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_usage_and_exit - print usage and exit 97
 */
static void print_usage_and_exit(void)
{
	dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	exit(97);
}

/**
 * main - copies the content of a file to another file
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, exits with error codes on failure
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	ssize_t r, w, written;
	char buffer[1024];

	if (argc != 3)
		print_usage_and_exit();

	/* open source */
	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	/* open/create destination with 0664, truncate if exists */
	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		close(fd_from);
		exit(99);
	}

	/* copy loop: read 1024 and write fully (handle partial writes) */
	while (1)
	{
		r = read(fd_from, buffer, 1024);
		if (r == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
			close(fd_from);
			close(fd_to);
			exit(98);
		}
		if (r == 0)
			break;

		written = 0;
		while (written < r)
		{
			w = write(fd_to, buffer + written, r - written);
			if (w == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
				close(fd_from);
				close(fd_to);
				exit(99);
			}
			written += w;
		}
	}

	/* close fds with correct fd value in message */
	if (close(fd_from) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
		exit(100);
	}
	if (close(fd_to) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
		exit(100);
	}

	return (0);
}
