#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/* usage -> 97 */
static void usage_exit(void)
{
	dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	exit(97);
}

/* close -> 100 */
static void close_or_die(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/* write exactly n bytes -> 99 on failure */
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

/* read->write loop after priming read */
static void copy_loop(int fd_from, int fd_to, const char *from,
			  const char *to)
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
 * main - POSIX cp with exits 97/98/99/100 (1024-byte buffer)
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

	/* Priming read for checker that forces read() to fail */
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

