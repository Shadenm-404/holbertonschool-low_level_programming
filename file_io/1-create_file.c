cd ~/holbertonschool-low_level_programming/file_io

cat > 1-create_file.c <<'EOF'
#include "main.h"

/**
 * create_file - creates a file and writes text_content into it
 * @filename: name of the file to create
 * @text_content: NULL terminated string to write to the file
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
		while (text_content[len])
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
EOF

