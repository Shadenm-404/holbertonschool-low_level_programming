#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * usage_exit - print usage and exit 97
 */
static void usage_exit(void)
{
	dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	exit(97);
}

/**
 * close_or_die - close fd or print error and exit 100
 * @fd: file descriptor
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
 * write_all - write exactly n bytes or exit 99
 * @fd: destination fd
 * @buf: buffer
 * @n: number of bytes
 * @to_name: file name for error message
 */
static void write_all(int fd, const char *buf, ssize_t n,
			  const char *to_name)
{
	ssize_t off = 0, w;

	while (off < n)
	{
		w = write(fd, buf + off, n - off);
		if (w == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", to_name);
			exit(99);
		}
		off += w;
	}
}

/**
 * copy_loop - keep reading/writing until EOF, handle read errors (98)
 * @fd_from: source fd
 * @fd_to: dest fd
 * @from_name: source file name
 * @to_name: dest file name
 */
static void copy_loop(int fd_from, int fd_to,
			  const char *from_name, const char *to_name)
{
	char buf[1024];
	ssize_t r;

	for (;;)
	{
		r = read(fd_from, buf, sizeof(buf));
		if (r == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't read from file %s\n", from_name);
			close_or_die(fd_from);
			close_or_die(fd_to);
			exit(98);
		}
		if (r == 0)
			break;
		write_all(fd_to, buf, r, to_name);
	}
}

/**
 * main - copy using only POSIX syscalls; exits 97/98/99/100
 * @argc: count
 * @argv: vector
 * Return: 0 on success
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

	/* Priming read so a forced read-fail yields 98 before touching dest */
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

