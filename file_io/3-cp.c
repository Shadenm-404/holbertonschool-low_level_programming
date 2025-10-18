#include <stdio.h>      /* dprintf */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /* read, write, close */
#include <fcntl.h>      /* open */
#include <sys/stat.h>   /* modes */
#include "main.h"       /* اختياري، موجود عندك */

#define BUF_SIZE 1024

/* ===== Helpers (≤ 5 functions إجمالاً) ===== */

static void close_fail(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

static void read_fail(const char *file, int fd_from, int fd_to, int to_opened)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
	close_fail(fd_from);
	if (to_opened)
		close_fail(fd_to);
	exit(98);
}

static void write_fail(const char *file, int fd_from, int fd_to)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
	close_fail(fd_from);
	close_fail(fd_to);
	exit(99);
}

static void write_all(int fd_to, char *buf, ssize_t n,
		      const char *file_to, int fd_from)
{
	ssize_t off = 0, w;

	while (off < n)
	{
		w = write(fd_to, buf + off, n - off);
		if (w == -1)
			write_fail(file_to, fd_from, fd_to);
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
	int fd_from, fd_to;
	ssize_t r;
	char buf[BUF_SIZE];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	/* افتح المصدر */
	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		exit(98);
	}

	/* أول read: إن فشلت نخرج 98 بدون فتح الوجهة */
	r = read(fd_from, buf, BUF_SIZE);
	if (r == -1)
		read_fail(av[1], fd_from, -1, 0);

	/* الآن فقط افتح الوجهة */
	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
		close_fail(fd_from);
		exit(99);
	}

	/* اكتب الدفعة الأولى ثم أكمل بقيتها */
	while (r > 0)
	{
		write_all(fd_to, buf, r, av[2], fd_from);

		r = read(fd_from, buf, BUF_SIZE);
		if (r == -1)
			read_fail(av[1], fd_from, fd_to, 1);
	}

	/* إغلاقات آمنة */
	close_fail(fd_from);
	close_fail(fd_to);
	return (0);
}
