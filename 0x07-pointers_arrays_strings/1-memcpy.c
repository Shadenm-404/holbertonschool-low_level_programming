#include "main.h"
/**
 * _memcpy - ينسخ n بايت من src إلى dest (بدون دعم التداخل)
 * @dest: وجهة النسخ
 * @src: مصدر النسخ
 * @n: عدد البايتات
 * Return: dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
    unsigned int i;
    for (i = 0; i < n; i++)
        dest[i] = src[i];
    return dest;
}
