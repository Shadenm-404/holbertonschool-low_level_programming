#include "main.h"

/**
<<<<<<< HEAD
 * append_text_to_file - appends text at the end of a file
 * @filename: name of the file
=======
 * append_text_to_file - appends text at end of a file
 * @filename: file name
>>>>>>> 5dbba34 (Initialize repo and add file_io tasks)
 * @text_content: NULL-terminated string to append
 *
 * Return: 1 on success, -1 on failure
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int fd;
<<<<<<< HEAD
	ssize_t w, total = 0;
	ssize_t len = 0;
=======
	ssize_t w, total = 0, len = 0;
>>>>>>> 5dbba34 (Initialize repo and add file_io tasks)

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (-1);

	if (text_content == NULL)
	{
		close(fd);
		return (1);
	}

	while (text_content[len] != '\0')
		len++;

	while (total < len)
	{
		w = write(fd, text_content + total, len - total);
		if (w == -1)
		{
			close(fd);
			return (-1);
		}
		total += w;
	}

	close(fd);
	return (1);
}
