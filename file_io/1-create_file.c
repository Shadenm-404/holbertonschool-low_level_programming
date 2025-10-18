#include "main.h"

/**
 * create_file - creates a file and writes text
<<<<<<< HEAD
 * @filename: name of the file to create
 * @text_content: string to write (NULL creates empty file)
=======
 * @filename: file name
 * @text_content: string to write (NULL -> empty)
>>>>>>> 5dbba34 (Initialize repo and add file_io tasks)
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int fd;
	ssize_t wbytes, len = 0;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	if (text_content != NULL)
	{
		while (text_content[len] != '\0')
			len++;

		wbytes = write(fd, text_content, len);
		if (wbytes == -1 || wbytes != len)
		{
			close(fd);
			return (-1);
		}
	}

	close(fd);
	return (1);
}
