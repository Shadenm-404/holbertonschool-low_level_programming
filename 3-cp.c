#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 1024

/**
 * closing - close a file descriptor or exit(100) on failure
 * @fd: file descriptor to close
 */
static void closing(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * copy_file - copy content from file_from to file_to using 1KB buffer
 * @file_from: source path
 * @file_to: destination path
 * Return: 0 on success
 */
static int copy_file(const char *file_from, const char *file_to)
{
	int fd_from, fd_to;
	ssize_t r, w, off;
	char buf[BUF_SIZE];

	fd_from = open(file_from, O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		exit(98);
	}

	fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
		closing(fd_from);
		exit(99);
	}

	while ((r = read(fd_from, buf, BUF_SIZE)) > 0)
	{
		off = 0;
		while (off < r)
		{
			w = write(fd_to, buf + off, r - off);
			if (w == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
				closing(fd_from);
				closing(fd_to);
				exit(99);
			}
			off += w;
		}
	}
	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		closing(fd_from);
		closing(fd_to);
		exit(98);
	}

	closing(fd_from);
	closing(fd_to);
	return (0);
}

/**
 * main - entry point
 * @argc: args count
 * @argv: args vector
 * Return: 0 on success, exits with 97 on wrong usage
 */
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	return (copy_file(argv[1], argv[2]));
}
