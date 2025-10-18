#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* Buffer size per task requirement */
#define BUF_SIZE 1024

char *create_buffer(const char *file);
void close_fd(int fd);
int cp(const char *file_from, const char *file_to);

#endif /* MAIN_H */
