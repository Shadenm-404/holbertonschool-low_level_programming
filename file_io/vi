#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

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

    fd_from = open(av[1], O_RDONLY);
    if (fd_from == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
        exit(98);
    }

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

    while ((r = read(fd_from, buf, BUF_SIZE)) > 0)
    {
        ssize_t off = 0;

        while (off < r)
        {
            w = write(fd_to, buf + off, r - off);
            if (w == -1)
            {
                dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
                close(fd_from);
                close(fd_to);
                exit(99);
            }
            off += w;
        }
    }

    if (r == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
        close(fd_from);
        close(fd_to);
        exit(98);
    }

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
