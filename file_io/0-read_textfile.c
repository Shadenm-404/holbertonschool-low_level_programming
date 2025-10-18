#include <stdlib.h>
#include "main.h"

/**
 * read_textfile - reads a text file and prints it to STDOUT
 * @filename: path to file
 * @letters: max bytes to read and print
 *
 * Return: number of bytes printed, or 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t rbytes, wbytes, total = 0;
	char *buf;

	if (filename == NULL || letters == 0)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	buf = (char *)malloc(letters);
	if (buf == NULL)
	{
		close(fd);
		return (0);
	}

	rbytes = read(fd, buf, letters);
	if (rbytes == -1)
	{
		free(buf);
		close(fd);
		return (0);
	}

	while (total < rbytes)
	{
		wbytes = write(STDOUT_FILENO, buf + total, rbytes - total);
		if (wbytes == -1)
		{
			free(buf);
			close(fd);
			return (0);
		}
		total += wbytes;
	}

	free(buf);
	close(fd);
	return (total);
}

