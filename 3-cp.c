#include "main.h"

/**
 * create_buffer - Allocate a 1KB buffer for file I/O.
 * @file: Name of the output file (for error message context).
 *
 * Return: Pointer to the allocated buffer.
 * Exit: 99 if allocation fails.
 */
char *create_buffer(const char *file)
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
 * close_fd - Close a file descriptor with error check.
 * @fd: The file descriptor to close.
 *
 * Exit: 100 if close(2) fails.
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * cp - Copy content from one file to another using a 1KB buffer.
 * @file_from: Source file path.
 * @file_to: Destination file path.
 *
 * Return: 0 on success.
 * Exit: 98 on read errors, 99 on write/create errors.
 */
int cp(const char *file_from, const char *file_to)
{
	int fd_from, fd_to, r, w;
	char *buffer = create_buffer(file_to);

	fd_from = open(file_from, O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		free(buffer), exit(98);
	}
	fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
		free(buffer), close_fd(fd_from), exit(99);
	}

	while ((r = read(fd_from, buffer, BUF_SIZE)) > 0)
	{
		w = write(fd_to, buffer, r);
		if (w != r)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
			free(buffer), close_fd(fd_from), close_fd(fd_to), exit(99);
		}
	}
	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		free(buffer), close_fd(fd_from), close_fd(fd_to), exit(98);
	}

	free(buffer);
	close_fd(fd_from);
	close_fd(fd_to);
	return (0);
}

/**
 * main - Entry point: validate args and copy a file.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success.
 * Exit: 97 if usage is wrong.
 */
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	return (cp(argv[1], argv[2]));
}
