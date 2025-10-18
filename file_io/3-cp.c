#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_usage_and_exit - prints usage and exits with code 97
 */
static void print_usage_and_exit(void)
{
	dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	exit(97);
}

/**
 * close_or_die - closes fd or exits with 100 on failure
 * @fd: file descriptor to close
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
 * write_fully - writes exactly n bytes; exits 99 on failure
 * @fd: destination fd
 * @buf: buffer
 * @n: number of bytes
 * @to_name: dest file name (for message)
 */
static void write_fully(int fd, const char *buf, ssize_t n, const char *to_name)
{
	ssize_t off = 0, w;

	while (off < n)
	{
		w = write(fd, buf + off, n - off);
		if (w == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", to_name);
			exit(99);
		}
		off += w;
	}
}

/**
 * main - copies file_from to file_to (POSIX I/O only)
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	ssize_t r;
	char buf[1024];

	if (argc != 3)
		print_usage_and_exit();

	/* افتح المصدر */
	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	/* جرّب القراءة أولاً قبل فتح الوجهة لضمان 98 عند فشل read */
	r = read(fd_from, buf, 1024);
	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		close_or_die(fd_from);
		exit(98);
	}

	/* افتح/أنشئ الوجهة الآن */
	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		close_or_die(fd_from);
		exit(99);
	}

	/* اكتب أول كتلة لو كانت القراءة نجحت */
	if (r > 0)
		write_fully(fd_to, buf, r, argv[2]);

	/* كمّل النسخ */
	while (1)
	{
		r = read(fd_from, buf, 1024);
		if (r == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
			close_or_die(fd_from);
			close_or_die(fd_to);
			exit(98);
		}
		if (r == 0)
			break;

		write_fully(fd_to, buf, r, argv[2]);
	}

	close_or_die(fd_from);
	close_or_die(fd_to);
	return (0);
}

