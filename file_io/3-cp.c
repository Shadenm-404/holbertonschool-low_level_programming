#include "main.h"
#include <stdio.h>
#include <stdlib.h>

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
static void write_fully(int fd, const char *buf, ssize_t n,
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

/* open source -> 98 on failure */
static int open_source(const char *from)
{
	int fd = open(from, O_RDONLY);

	if (fd == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", from);
		exit(98);
	}
	return (fd);
}

/* open/create dest (0664) -> 99 on failure */
static int open_dest(const char *to)
{
	int fd = open(to, O_WRONLY | O_CREAT | O_TRUNC, 0664);

	if (fd == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", to);
		exit(99);
	}
	return (fd);
}

/* copy remaining chunks after the priming read */
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
		write_fully(fd_to, buf, r, to_name);
	}
}

/**
 * main - copy file_from to file_to using POSIX I/O
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, exits with 97/98/99/100 on failure
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	char buf[1024];
	ssize_t r;

	if (argc != 3)
		usage_exit();

	/* 1) افتح المصدر */
	fd_from = open_source(argv[1]);

	/* 2) القراءة التمهيدية قبل فتح الوجهة */
	r = read(fd_from, buf, sizeof(buf));
	if (r == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		close_or_die(fd_from);
		exit(98);
	}

	/* 3) الآن افتح/أنشئ الوجهة */
	fd_to = open_dest(argv[2]);

	/* 4) اكتب التشنك الأول (إن وُجد) */
	if (r > 0)
		write_fully(fd_to, buf, r, argv[2]);

	/* 5) كمّل النسخ حتى EOF */
	copy_loop(fd_from, fd_to, argv[1], argv[2]);

	close_or_die(fd_from);
	close_or_die(fd_to);
	return (0);
}

