#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* Prototypes */
static void usage_exit(void);
static void read_error_exit(const char *file);
static void write_error_exit(const char *file);
static void close_error_exit(int fd);
static int  open_src(const char *path);
static int  open_dst(const char *path);
static void copy_loop(int fd_from, int fd_to,
		      const char *src_name, const char *dst_name);
static int  process_copy(char *src, char *dst);

static void usage_exit(void)
{
	dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	exit(97);
}

static void read_error_exit(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
	exit(98);
}

static void write_error_exit(const char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
	exit(99);
}

static void close_error_exit(int fd)
{
	dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
	exit(100);
}

static int open_src(const char *path)
{
	int fd = open(path, O_RDONLY);

	if (fd == -1)
		read_error_exit(path);
	return (fd);
}

static int open_dst(const char *path)
{
	int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);

	if (fd == -1)
		write_error_exit(path);
	return (fd);
}

static void copy_loop(int fd_from, int fd_to,
		      const char *src_name, const char *dst_name)
{
	ssize_t r, w;
	char buf[1024];

	while (1)
	{
		r = read(fd_from, buf, sizeof(buf));
		if (r == -1)
			read_error_exit(src_name);
		if (r == 0)
			break;
		w = write(fd_to, buf, r);
		if (w == -1 || w != r)
			write_error_exit(dst_name);
	}
}

static int process_copy(char *src, char *dst)
{
	int fd_from, fd_to, c1, c2;

	fd_from = open_src(src);
	fd_to = open_dst(dst);
	copy_loop(fd_from, fd_to, src, dst);

	c1 = close(fd_from);
	if (c1 == -1)
		close_error_exit(fd_from);
	c2 = close(fd_to);
	if (c2 == -1)
		close_error_exit(fd_to);
	return (0);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		usage_exit();
	return (process_copy(argv[1], argv[2]));
}
