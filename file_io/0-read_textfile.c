#include <stdlib.h>
#include "main.h"

/**
<<<<<<< HEAD
 * read_textfile - reads a text file and prints it to POSIX standard output
 * @filename: path to the file
 * @letters: maximum number of bytes to read and print
 *
 * Return: actual number of bytes printed, or 0 on any failure
=======
 * read_textfile - reads a text file and prints it to STDOUT
 * @filename: path to file
 * @letters: max bytes to read and print
 *
 * Return: bytes printed, or 0 on failure
>>>>>>> 5dbba34 (Initialize repo and add file_io tasks)
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
<<<<<<< HEAD
	ssize_t rbytes, wbytes, wtotal = 0;
=======
	ssize_t rbytes, wbytes, total = 0;
>>>>>>> 5dbba34 (Initialize repo and add file_io tasks)
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

<<<<<<< HEAD
	while (wtotal < rbytes)
	{
		wbytes = write(STDOUT_FILENO, buf + wtotal, rbytes - wtotal);
=======
	while (total < rbytes)
	{
		wbytes = write(STDOUT_FILENO, buf + total, rbytes - total);
>>>>>>> 5dbba34 (Initialize repo and add file_io tasks)
		if (wbytes == -1)
		{
			free(buf);
			close(fd);
			return (0);
		}
<<<<<<< HEAD
		wtotal += wbytes;
=======
		total += wbytes;
>>>>>>> 5dbba34 (Initialize repo and add file_io tasks)
	}

	free(buf);
	close(fd);
<<<<<<< HEAD
	return (wtotal);
}

=======
	return (total);
}
>>>>>>> 5dbba34 (Initialize repo and add file_io tasks)
