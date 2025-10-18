#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* Prototypes */
static void usage_exit(void);
static void read_error_exit(const char *f);
static void write_error_exit(const char *f);
static void close_error_exit(int fd);
static int  open_src(const char *p);
static int  open_dst(const char *p);
static void copy_loop(int ff, int ft, const char *sn, const char *dn);
static int  process_copy(char *src, char *dst);

static void usage_exit(void)
{
	dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
	exit(97);
}

static void read_error_exit(const char *f)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", f);
	exit(98);
}

static void write_error_exit(const char *f)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", f);
	exit(99);
}

static void close_error_exit(int fd)
{
	dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
	exit(100);
}

static int open_src(const char *p)
{
	int fd = open(p, O_RDONLY);

	if (fd == -1)
		read_error_exit(p);
	return (fd);
}

static int open_dst(const char *p)
{
	int fd = open(p, O_WRONLY | O_CREAT | O_TRUNC, 0664);

	if (fd == -1)
		write_error_exit(p);
	return (fd);
}

static void copy_loop(int ff, int ft, const char *sn, const char *dn)
{
	char buf[1024];
	ssize_t r, w;

	while (1)
	{
		r = read(ff, buf, sizeof(buf));
		if (r == -1)
			read_error_exit(sn);
		if (r == 0)
			break;
		w = write(ft, buf, r);
		if (w == -1 || w != r)
			write_error_exit(dn);
	}
}

static int process_copy(char *src, char *dst)
{
	int ff = open_src(src), ft = open_dst(dst);
	int c1 = 0, c2 = 0;

	copy_loop(ff, ft, src, dst);

	c1 = close(ff);
	if (c1 == -1)
		close_error_exit(ff);
	c2 = close(ft);
	if (c2 == -1)
		close_error_exit(ft);
	return (0);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		usage_exit();
	return (process_copy(argv[1], argv[2]));
}
