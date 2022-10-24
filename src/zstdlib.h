#ifndef Z_STDLIB_H
#define Z_STDLIB_H

#include <zstddef.h>

#ifndef ZCC_EXIT_FAILURE
    #define ZCC_EXIT_FAILURE 1
#endif

#ifndef ZCC_EXIT_SUCCESS
    #define ZCC_EXIT_SUCCESS 0
#endif

void zexit(int status);
void* zmalloc(size_t size);
void zfree(void* ptr);
long zatol(const char* str);
int zatoi(const char* str);
int zitoa(int num, char* str, const int base);
long zstrtol(const char* str, char** endptr, int base);

#endif

