#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * usage_exit - Print usage to STDERR and exit with code 97.
 */
static void usage_exit(void)
{
	dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	exit(97);
}

/**
 * close_or_die - Close a file descriptor or exit with code 100 on error.
 * @fd: File descriptor to close.
 *
 * Return: Nothing (exits on failure).
 */
static void close_or_die(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * write_all - Write exactly @n bytes or exit with code 99 on failure.
 * @fd: Destination file descriptor.
 * @buf: Buffer to write from.
 * @n: Number of bytes to write.
 * @to: Destination filename (for error message).
 *
 * Return: Nothing (exits on failure).
 */
static void write_all(int fd, const char *buf, ssize_t n, const char *to)
{
	ssize_t off = 0, w;

	while (off < n)
	{
		w = write(fd, buf + off, n - off);
		if (w == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", to);
			exit(99);
		}
		off += w;
	}
}

/**
 * copy_loop - Read chunks from @fd_from and write to @fd_to.
 * @fd_from: Source file descriptor.
 * @fd_to: Destination file descriptor.
 * @from: Source filename (for error message).
 * @to: Destination filename (for error message).
 *
 * Return: Nothing (exits 98/99 on failure).
 */
static void copy_loop(int fd_from, int fd_to, const char *from, const char *to)
{
	char buf[1024];
	ssize_t r;

	for (;;)
	{
		r = read(fd_from, buf, sizeof(buf));
		if (r == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't read from file %s\n", from);
			close_or_die(fd_from);
			close_or_die(fd_to);
			exit(98);
		}
		if (r == 0)
			break;
		write_all(fd_to, buf, r, to);
	}
}

/**
 * main - Copy a file using POSIX I/O.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success. Exits with 97/98/99/100 on failure.
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	char buf[1024];
	ssize_t r;

	if (argc != 3)
		usage_exit();

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	/* Priming read: ensure read-failure yields 98 before touching dest. */
	r = read(fd_from, buf, sizeof(buf));
	if (r == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		close_or_die(fd_from);
		exit(98);
	}

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", argv[2]);
		close_or_die(fd_from);
		exit(99);
	}

	if (r > 0)
		write_all(fd_to, buf, r, argv[2]);

	copy_loop(fd_from, fd_to, argv[1], argv[2]);

	close_or_die(fd_from);
	close_or_die(fd_to);
	return (0);
}

