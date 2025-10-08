/**
 * SpiritOS Freestanding C Library - String Functions
 * 
 * Basic string functions for freestanding environment
 */

#ifndef KSTRING_H
#define KSTRING_H

#include <stddef.h>

/* String find substring */
char *strstr(const char *haystack, const char *needle);

/* String duplicate (stub - returns NULL) */
char *strdup(const char *s);

/* String copy with limit */
char *strncpy(char *dest, const char *src, size_t n);

/* String length */
size_t strlen(const char *str);

/* String copy */
char *strcpy(char *dest, const char *src);

/* String compare */
int strcmp(const char *s1, const char *s2);

/* Memory copy */
void *memcpy(void *dest, const void *src, size_t n);

/* Memory set */
void *memset(void *s, int c, size_t n);

/* Memory compare */
int memcmp(const void *s1, const void *s2, size_t n);

#endif /* KSTRING_H */
