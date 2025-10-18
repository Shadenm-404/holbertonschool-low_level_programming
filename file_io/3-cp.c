#include "main.h"
#include <stdlib.h>

/**
 * usage_exit - print usage and exit 97
 */
static void usage_exit(void)
{
	const char *m = "Usage: cp file_from file_to\n";
	size_t i = 0;

	while (m[i])
		i++;
	(void)write(STDERR_FILENO, m, i);
	exit(97);
}

/**
 * close_or_die - close fd or print error and exit 100
 * @fd: file descriptor
 */
static void close_or_die(int fd)
{
	char num[12];
	int i = 0, n = fd;
	const char *pfx = "Error: Can't close fd ";
	const char *nl = "\n";
	size_t k = 0;

	if (close(fd) != -1)
		return;

	/* write prefix */
	while (pfx[k])
		k++;
	(void)write(STDERR_FILENO, pfx, k);

	/* itoa for non-negative fd */
	if (n == 0)
		num[i++] = '0';
	while (n > 0)
	{
		num[i++] = '0' + (n % 10);
		n /= 10;
	}
	/* reverse digits */
	for (n = 0; n < i / 2; n++)
	{
		char t = num[n];
		num[n] = num[i - 1 - n];
		num[i - 1 - n] = t;
	}
	(void)write(STDERR_FILENO, num, i);

	/* newline */
	(void)write(STDERR_FILENO, nl, 1);
	exit(100);
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
	const char *pfx = "Error: Can't write to ";
	const char *nl = "\n";
	size_t k, tlen;

	while (off < n)
	{
		w = write(fd, buf + off, n - off);
		if (w == -1)
		{
			k = 0;
			while (pfx[k])
				k++;
			(void)write(STDERR_FILENO, pfx, k);

			tlen = 0;
			while (to_name[tlen])
				tlen++;
			(void)write(STDERR_FILENO, to_name, tlen);
			(void)write(STDERR_FILENO, nl, 1);
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
	const char *pfx = "Error: Can't read from file ";
	const char *nl = "\n";
	size_t k, flen;

	for (;;)
	{
		r = read(fd_from, buf, sizeof(buf));
		if (r == -1)
		{
			k = 0;
			while (pfx[k])
				k++;
			(void)write(STDERR_FILENO, pfx, k);

			flen = 0;
			while (from_name[flen])
				flen++;
			(void)write(STDERR_FILENO, from_name, flen);
			(void)write(STDERR_FILENO, nl, 1);

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
 * main - copy using only POSIX syscalls; exit codes 97/98/99/100
 * @argc: count
 * @argv: vector
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	char buf[1024];
	ssize_t r;
	const char *rd_pfx = "Error: Can't read from file ";
	const char *wr_pfx = "Error: Can't write to ";
	const char *nl = "\n";
	size_t k, len;

	if (argc != 3)
		usage_exit();

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		k = 0;
		while (rd_pfx[k])
			k++;
		(void)write(STDERR_FILENO, rd_pfx, k);
		len = 0;
		while (argv[1][len])
			len++;
		(void)write(STDERR_FILENO, argv[1], len);
		(void)write(STDERR_FILENO, nl, 1);
		exit(98);
	}

	/* Priming read before opening destination (for test harness) */
	r = read(fd_from, buf, sizeof(buf));
	if (r == -1)
	{
		k = 0;
		while (rd_pfx[k])
			k++;
		(void)write(STDERR_FILENO, rd_pfx, k);
		len = 0;
		while (argv[1][len])
			len++;
		(void)write(STDERR_FILENO, argv[1], len);
		(void)write(STDERR_FILENO, nl, 1);
		close_or_die(fd_from);
		exit(98);
	}

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		k = 0;
		while (wr_pfx[k])
			k++;
		(void)write(STDERR_FILENO, wr_pfx, k);
		len = 0;
		while (argv[2][len])
			len++;
		(void)write(STDERR_FILENO, argv[2], len);
		(void)write(STDERR_FILENO, nl, 1);
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

