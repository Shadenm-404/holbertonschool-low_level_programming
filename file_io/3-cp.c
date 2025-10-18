#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * usage_exit - Print usage and exit with code 97.
 */
static void usage_exit(void)
{
	dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	exit(97);
}

/**
 * close_or_die - Close a file descriptor or exit 100 on failure.
 * @fd: File descriptor to close.
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
 * write_all - Write exactly n bytes or exit 99 on failure.
 * @fd: Destination fd.
 * @buf: Buffer.
 * @n: Bytes to write.
 * @to: File name for error message.
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
 * copy_loop - Copy from source to destination.
 * @fd_from: Source fd.
 * @fd_to: Destination fd.
 * @from: Source filename.
 * @to: Destination filename.
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
 * setup_fds - Open both source and destination, and do priming read.
 * @argv: Argument vector.
 * @buf: Buffer (for priming read).
 * @r: Pointer to store read result.
 * Return: fd_to (opened destination fd).
 */
static int setup_fds(char *argv[], char *buf, ssize_t *r)
{
	int fd_from, fd_to;

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	*r = read(fd_from, buf, sizeof(buf));
	if (*r == -1)
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

	if (*r > 0)
		write_all(fd_to, buf, *r, argv[2]);

	close_or_die(fd_from);
	return (fd_to);
}

/**
 * main - Copy file_from to file_to using POSIX I/O.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: 0 on success, exits 97/98/99/100 on failure.
 */
int main(int argc, char *argv[])
{
	int fd_to;
	char buf[1024];
	ssize_t r;

	if (argc != 3)
		usage_exit();

	fd_to = setup_fds(argv, buf, &r);
	copy_loop(open(argv[1], O_RDONLY), fd_to, argv[1], argv[2]);
	close_or_die(fd_to);
	return (0);
}

