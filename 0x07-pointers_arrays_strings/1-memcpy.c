#include "main.h"

/**
 * _memcpy - copy n bytes from src to dest (no support for overlap)
 * @dest: destination buffer
 * @src:  source buffer
 * @n:    number of bytes to copy
 *
 * Return: pointer to dest
 *
 * Note: behavior is undefined if memory regions overlap (like standard memcpy).
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        dest[i] = src[i];

    return dest;
}
