#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

/* ---------- helpers ---------- */

static void close_fail(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

static void write_all(int fd_to, char *buf, ssize_t n,
		      const char *file_to, int fd_from)
{
	ssize_t off = 0, w;

	while (off < n)
	{
		w = write(fd_to, buf + off, n - off);
		if (w == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n",
				file_to);
			close_fail(fd_from);
			close_fail(fd_to);
			exit(99);
		}
		off += w;
	}
}

static void first_read_open_from(const char *src, int *pfd_from,
				 char *buf, ssize_t *pr)
{
	*pfd_from = open(src, O_RDONLY);
	if (*pfd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", src);
		exit(98);
	}

	*pr = read(*pfd_from, buf, BUF_SIZE);
	if (*pr == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", src);
		close_fail(*pfd_from);
		exit(98);
	}
}

static void copy_rest(int fd_from, const char *src, const char *dst,
		      char *buf, ssize_t r)
{
	int fd_to;

	fd_to = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", dst);
		close_fail(fd_from);
		exit(99);
	}

	while (r > 0)
	{
		write_all(fd_to, buf, r, dst, fd_from);
		r = read(fd_from, buf, BUF_SIZE);
		if (r == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n",
				src);
			close_fail(fd_from);
			close_fail(fd_to);
			exit(98);
		}
	}

	close_fail(fd_from);
	close_fail(fd_to);
}

/**
 * main - copy content of a file to another file
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success; exits 97/98/99/100 on error
 */
int main(int ac, char **av)
{
	int fd_from;
	ssize_t r;
	char buf[BUF_SIZE];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	first_read_open_from(av[1], &fd_from, buf, &r);
	copy_rest(fd_from, av[1], av[2], buf, r);
	return (0);
}
