#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 1024

/**
 * create_buffer - allocate a 1KB buffer and handle allocation error.
 * @file: file name used in the error message context.
 * Return: pointer to buffer.
 * Exit: 99 on allocation failure.
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
 * close_fd - close a file descriptor, exiting with code 100 on failure.
 * @fd: file descriptor to close.
 */
static void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copy the content of a file to another file.
 * @argc: argument count.
 * @argv: argument vector.
 *
 * Usage: cp file_from file_to
 * Exit codes:
 * 97: wrong number of args
 * 98: read error on file_from
 * 99: write/create error on file_to or buffer allocation error
 * 100: close error
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	int fd_from, fd_to, r, w;
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
		free(buffer), exit(98);
	}

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		free(buffer), close_fd(fd_from), exit(99);
	}

	while ((r = read(fd_from, buffer, BUF_SIZE)) > 0)
	{
		w = write(fd_to, buffer, r);
		if (w != r)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
			free(buffer), close_fd(fd_from), close_fd(fd_to), exit(99);
		}
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		free(buffer), close_fd(fd_from), close_fd(fd_to), exit(98);
	}

	free(buffer);
	close_fd(fd_from);
	close_fd(fd_to);
	return (0);
}
