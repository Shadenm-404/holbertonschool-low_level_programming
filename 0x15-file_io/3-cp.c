#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char *create_buffer(char *file);
void close_file(int fd);

/* Alloc 1024 bytes (exit 99 on fail) */
char *create_buffer(char *file)
{
	char *buffer = malloc(1024);

	if (buffer == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
		exit(99);
	}
	return (buffer);
}

/* Safe close (exit 100 on fail) */
void close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/*
 * cp: exit codes
 * 97 - wrong args
 * 98 - read error (file_from)
 * 99 - write/create error (file_to)
 * 100 - close error
 */
int main(int argc, char *argv[])
{
	int from, to;
	ssize_t r, w, written;
	char *buffer;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		return (97);
	}

	buffer = create_buffer(argv[2]);

	from = open(argv[1], O_RDONLY);
	if (from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		free(buffer);
		return (98);
	}

	/* اقرأ أولاً. لو فشلت القراءة ← 98 بدون فتح file_to */
	r = read(from, buffer, 1024);
	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		free(buffer);
		close_file(from);
		return (98);
	}

	/* افتح file_to فقط بعد نجاح أول read */
	to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		free(buffer);
		close_file(from);
		return (99);
	}

	/* اكتب الـ chunk الأول، ثم أكمل حلقات read/write */
	while (r > 0)
	{
		written = 0;
		while (written < r)
		{
			w = write(to, buffer + written, r - written);
			if (w == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
				free(buffer);
				close_file(from);
				close_file(to);
				return (99);
			}
			written += w;
		}

		r = read(from, buffer, 1024);
		if (r == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
			free(buffer);
			close_file(from);
			close_file(to);
			return (98);
		}
	}

	free(buffer);
	close_file(from);
	close_file(to);
	return (0);
}
