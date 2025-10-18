#include <stdio.h>      /* dprintf */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /* read, write, close */
#include <fcntl.h>      /* open */
#include <sys/stat.h>   /* modes */

#define BUF_SIZE 1024

/**
 * main - copy content of a file to another file
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success; exits 97/98/99/100 on error
 */
int main(int ac, char **av)
{
	int fd_from, fd_to, c1, c2;
	ssize_t r, w;
	char buf[BUF_SIZE];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	/* افتح المصدر وتحقق من القراءة قبل أي كتابة/فتح للوجهة */
	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		exit(98);
	}

	/* أول قراءة: لو فشلت نخرج 98 فورًا بدون فتح الوجهة */
	r = read(fd_from, buf, BUF_SIZE);
	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		c1 = close(fd_from);
		if (c1 == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
			exit(100);
		}
		exit(98);
	}

	/* الآن فقط افتح الوجهة */
	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
		c1 = close(fd_from);
		if (c1 == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
			exit(100);
		}
		exit(99);
	}

	/* اكتب الدفعة الأولى المقروءة ثم أكمل بقية الدُفعات */
	do {
		ssize_t off = 0;

		while (off < r)
		{
			w = write(fd_to, buf + off, r - off);
			if (w == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
				c1 = close(fd_from);
				if (c1 == -1)
				{
					dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
					exit(100);
				}
				c2 = close(fd_to);
				if (c2 == -1)
				{
					dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
					exit(100);
				}
				exit(99);
			}
			off += w;
		}

		r = read(fd_from, buf, BUF_SIZE);
		if (r == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
			c1 = close(fd_from);
			if (c1 == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
				exit(100);
			}
			c2 = close(fd_to);
			if (c2 == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
				exit(100);
			}
			exit(98);
		}
	} while (r > 0);

	/* إغلاقات آمنة */
	c1 = close(fd_from);
	if (c1 == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
		exit(100);
	}
	c2 = close(fd_to);
	if (c2 == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
		exit(100);
	}

	return (0);
}
