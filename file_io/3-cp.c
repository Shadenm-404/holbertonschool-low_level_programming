#include <stdio.h>      /* dprintf */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /* read, write, close */
#include <fcntl.h>      /* open */
#include <sys/stat.h>   /* modes */

/* ===== Helpers (4 funcs total including main) ===== */

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
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
			close_fail(fd_from);
			close_fail(fd_to);
			exit(99);
		}
		off += w;
	}
}

static void copy_file(const char *src, const char *dst)
{
	int fd_from, fd_to;
	ssize_t r;
	char buf[1024];

	fd_from = open(src, O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", src);
		exit(98);
	}

	/* أول read: لو فشلت نخرج 98 بدون فتح الوجهة */
	r = read(fd_from, buf, sizeof(buf));
	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", src);
		close_fail(fd_from);
		exit(98);
	}

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
		r = read(fd_from, buf, sizeof(buf));
		if (r == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", src);
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
	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	copy_file(av[1], av[2]);
	return (0);
}
