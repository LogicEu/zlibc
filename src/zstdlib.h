#ifndef Z_STDLIB_H
#define Z_STDLIB_H

#include <zstddef.h>

#define Z_EXIT_FAILURE 1
#define Z_EXIT_SUCCESS 0

void zexit(int status);
void* zmalloc(size_t size);
void zfree(void* ptr);
long zatol(const char* str);
int zatoi(const char* str);
double zatof(const char* str);
int zitoa(int num, char* str, const int base);
long zstrtol(const char* str, char** endptr, int base);
double zstrtod(const char* str, char** endptr);

#endif /* Z_STDLIB_H */

