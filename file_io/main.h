cd file_io

cat > main.h <<'EOF'
#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Prototypes */
int _putchar(char c);
ssize_t read_textfile(const char *filename, size_t letters);

#endif /* MAIN_H */
EOF


