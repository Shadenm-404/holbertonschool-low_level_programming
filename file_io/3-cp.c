#include <stdio.h>      /* dprintf */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /* read, write, close */
#include <fcntl.h>      /* open */
#include <sys/stat.h>   /* modes */

#define BUF_SIZE 1024

static void exit_read(const char *file, int fd_from, int fd_to)
{
	dprintf(STDERR_FILENO,
		"Error: Can't read from file %s\n", file);
	if (fd_from >= 0 && close(fd_from) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_from);
		exit(100);
	}
	if (fd_to >= 0 && close(fd_to) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_to);
		exit(100);
	}
	exit(98);
}

static void exit_write(const char *file, int fd_from, int fd_to)
{
	dprintf(STDERR_FILENO,
		"Error: Can't write to %s\n", file);
	if (fd_from >= 0 && close(fd_from) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_from);
		exit(100);
	}
	if (fd_to >= 0 && close(fd_to) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_to);
		exit(100);
	}
	exit(99);
}

static void exit_close(int fd)
{
	dprintf(STDERR_FILENO,
		"Error: Can't close fd %d\n", fd);
	exit(100);
}

static void write_all(int fd_to, char *buf, ssize_t n,
		      const char *file_to, int fd_from)
{
	ssize_t off = 0, w;

	while (off < n)
	{
		w = write(fd_to, buf + off, n - off);
		if (w == -1)
			exit_write(file_to, fd_from, fd_to);
		off += w;
	}
}

/**
 * main - copy content of a file to another file
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success; exits 97/98/99/100 on error
 */
int main(int ac, char **av)
{
	int fd_from, fd_to, c1, c2;
	ssize_t r;
	char buf[BUF_SIZE];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO,
			"Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
		exit_read(av[1], -1, -1);

	/* أول قراءة: إن فشلت نخرج 98 بدون فتح الوجهة */
	r = read(fd_from, buf, BUF_SIZE);
	if (r == -1)
		exit_read(av[1], fd_from, -1);

	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		if (close(fd_from) == -1)
			exit_close(fd_from);
		exit_write(av[2], -1, -1);
	}

	/* اكتب الدفعة الأولى ثم أكمل بقية الدُفعات */
	do {
		write_all(fd_to, buf, r, av[2], fd_from);
		r = read(fd_from, buf, BUF_SIZE);
		if (r == -1)
			exit_read(av[1], fd_from, fd_to);
	} while (r > 0);

	c1 = close(fd_from);
	if (c1 == -1)
		exit_close(fd_from);
	c2 = close(fd_to);
	if (c2 == -1)
		exit_close(fd_to);

	return (0);
}
