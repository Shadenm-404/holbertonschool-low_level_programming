#include <unistd.h>  /* read, write, close */
#include <fcntl.h>   /* open, O_RDONLY */
#include <stdlib.h>  /* malloc, free */
#include "main.h"

/* يكتب كل n بايت أو يرجع -1 عند الفشل */
static ssize_t write_all(int fd, const char *buf, size_t n)
{
	ssize_t done = 0, w;

	while ((size_t)done < n)
	{
		w = write(fd, buf + done, n - done);
		if (w <= 0)
			return (-1);
		done += w;
	}
	return (done);
}

/**
 * read_textfile - reads a text file and prints to STDOUT
 * @filename: path to file
 * @letters: max bytes to read and print
 * Return: actual bytes printed, or 0 on any error
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t r;
	char *buf;

	if (!filename || letters == 0)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	buf = malloc(letters);
	if (!buf)
	{
		close(fd);
		return (0);
	}

	r = read(fd, buf, letters);
	if (r <= 0 || write_all(STDOUT_FILENO, buf, (size_t)r) == -1)
		r = 0;

	free(buf);
	close(fd);
	return (r);
}
