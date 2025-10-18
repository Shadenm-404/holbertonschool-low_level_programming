#include "main.h"
#include <stdio.h>

void close_fd(int fd);
void read_error(char *file, int fd_from, int fd_to);
void write_error(char *file, int fd_from, int fd_to);

/**
 * close_fd - closes a file descriptor
 * @fd: file descriptor to close
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
 * read_error - handles read error
 * @file: filename
 * @fd_from: source fd
 * @fd_to: destination fd
 */
void read_error(char *file, int fd_from, int fd_to)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
	if (fd_from != -1)
		close(fd_from);
	if (fd_to != -1)
		close(fd_to);
	exit(98);
}

/**
 * write_error - handles write error
 * @file: filename
 * @fd_from: source fd
 * @fd_to: destination fd
 */
void write_error(char *file, int fd_from, int fd_to)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
	if (fd_from != -1)
		close(fd_from);
	if (fd_to != -1)
		close(fd_to);
	exit(99);
}

/**
 * main - copies content of a file to another file
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to, r, w;
	char buffer[1024];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		read_error(argv[1], -1, -1);

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
		write_error(argv[2], fd_from, -1);

	while ((r = read(fd_from, buffer, 1024)) > 0)
	{
		w = write(fd_to, buffer, r);
		if (w != r)
			write_error(argv[2], fd_from, fd_to);
	}

	if (r == -1)
		read_error(argv[1], fd_from, fd_to);

	close_fd(fd_from);
	close_fd(fd_to);

	return (0);
}
