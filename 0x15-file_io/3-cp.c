#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* ==== Prototypes ==== */
static void usage_exit(void);
static void read_error_exit(const char *file);
static void write_error_exit(const char *file);
static void close_file(int fd);
static int  open_src(const char *path);
static int  open_dst(const char *path);
static char *create_buffer(const char *file);

/**
 * usage_exit - print usage and exit 97
 */
static void usage_exit(void)
{
	dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	exit(97);
}

/**
 * read_error_exit - print read error and exit 98
 * @file: file name
 */
static void read_error_exit(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
	exit(98);
}

/**
 * write_error_exit - print write error and exit 99
 * @file: file name
 */
static void write_error_exit(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
	exit(99);
}

/**
 * close_file - close fd or exit 100 on error
 * @fd: file descriptor
 */
static void close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * create_buffer - Allocates 1024 bytes for a buffer.
 * @file: The name of the file buffer is storing chars for.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
static char *create_buffer(const char *file)
{
	char *buf = malloc(1024);

	if (buf == NULL)
	{
		/* Per spec: writing error message references the dst file */
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
		exit(99);
	}
	return (buf);
}

/**
 * open_src - open source file (read-only) or exit 98
 * @path: source path
 * Return: fd
 */
static int open_src(const char *path)
{
	int fd = open(path, O_RDONLY);

	if (fd == -1)
		read_error_exit(path);
	return (fd);
}

/**
 * open_dst - open/create destination (truncate) or exit 99
 * @path: destination path
 * Return: fd
 */
static int open_dst(const char *path)
{
	int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);

	if (fd == -1)
		write_error_exit(path);
	return (fd);
}

/**
 * main - copies the content of a file to another file
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	ssize_t r, w;
	char *buf;

	if (argc != 3)
		usage_exit();

	fd_from = open_src(argv[1]);
	fd_to = open_dst(argv[2]);
	buf = create_buffer(argv[2]);

	while (1)
	{
		r = read(fd_from, buf, 1024);
		if (r == -1)
		{
			free(buf);
			read_error_exit(argv[1]);
		}
		if (r == 0)
			break;

		w = write(fd_to, buf, r);
		if (w == -1 || w != r)
		{
			free(buf);
			write_error_exit(argv[2]);
		}
	}

	free(buf);
	close_file(fd_from);
	close_file(fd_to);
	return (0);
}
