/* 3-cp.c */
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024

static char *create_buffer(const char *file);
static void close_file(int fd);

/**
 * create_buffer - allocate a 1KB buffer.
 * @file: name of destination file (for error message).
 * Return: pointer to allocated buffer.
 */
static char *create_buffer(const char *file)
{
	char *buffer = malloc(BUF_SIZE);

	if (buffer == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
		exit(99);
	}
	return (buffer);
}

/**
 * close_file - close fd and handle error.
 * @fd: file descriptor to close.
 */
static void close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copy content of a file to another.
 * @argc: argument count.
 * @argv: argument vector.
 * Return: 0 on success.
 *
 * Exit codes:
 * 97 - wrong usage,
 * 98 - read error,
 * 99 - write/create error,
 * 100 - close error.
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	ssize_t r, w;
	char *buffer;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	buffer = create_buffer(argv[2]);

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		free(buffer);
		exit(98);
	}

	fd_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		free(buffer);
		close_file(fd_from);
		exit(99);
	}

	while ((r = read(fd_from, buffer, BUF_SIZE)) > 0)
	{
		ssize_t total = 0;

		while (total < r)
		{
			w = write(fd_to, buffer + total, r - total);
			if (w == -1)
			{
				dprintf(STDERR_FILENO,
					"Error: Can't write to %s\n", argv[2]);
				free(buffer);
				close_file(fd_from);
				close_file(fd_to);
				exit(99);
			}
			total += w;
		}
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		free(buffer);
		close_file(fd_from);
		close_file(fd_to);
		exit(98);
	}

	free(buffer);
	close_file(fd_from);
	close_file(fd_to);
	return (0);
}
