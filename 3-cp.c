/* 3-cp.c */
#include <stdio.h>      /* dprintf */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /* read, write, close, STDERR_FILENO */
#include <fcntl.h>      /* open */
#include <sys/stat.h>   /* mode constants */
#include <sys/types.h>  /* ssize_t */

#define BUF_SIZE 1024

static void close_or_die(int fd)
{
	int c = close(fd);

	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	char buf[BUF_SIZE];
	ssize_t r, w, off;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	/* If file exists, don't change its permissions; if created, set 0664 */
	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		close_or_die(fd_from); /* ensure fd_from gets closed or exit 100 */
		exit(99);
	}

	while ((r = read(fd_from, buf, BUF_SIZE)) > 0)
	{
		off = 0;
		while (off < r)
		{
			w = write(fd_to, buf + off, (size_t)(r - off));
			if (w == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
				close_or_die(fd_from);
				close_or_die(fd_to);
				exit(99);
			}
			off += w;
		}
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		close_or_die(fd_from);
		close_or_die(fd_to);
		exit(98);
	}

	close_or_die(fd_from);
	close_or_die(fd_to);
	return 0;
}
