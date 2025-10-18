#include <stdlib.h>
#include "main.h"

/**
 * write_all - write exactly n bytes to STDOUT
 * @buf: buffer
 * @n: number of bytes
 *
 * Return: bytes written, or -1 on error
 */
static ssize_t write_all(const char *buf, ssize_t n)
{
	ssize_t total = 0, w;

	while (total < n)
	{
		w = write(STDOUT_FILENO, buf + total, n - total);
		if (w == -1)
			return (-1);
		total += w;
	}
	return (total);
}

/**
 * read_textfile - reads a text file and prints it to STDOUT
 * @filename: path to file
 * @letters: max bytes to read and print
 *
 * Return: bytes printed, or 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t r;
	char *buf;

	if (filename == NULL || letters == 0)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	buf = malloc(letters);
	if (buf == NULL)
	{
		close(fd);
		return (0);
	}

	r = read(fd, buf, letters);
	if (r == -1 || write_all(buf, r) == -1)
		r = 0;

	free(buf);
	close(fd);
	return (r);
}

