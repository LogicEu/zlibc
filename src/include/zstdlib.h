#ifndef Z_STDLIB_H
#define Z_STDLIB_H

#include <zstddef.h>

#define Z_EXIT_FAILURE 1
#define Z_EXIT_SUCCESS 0

void zabort(void) __attribute__((noreturn));
void zexit(int status) __attribute__((noreturn));
int zatexit(void (*func)(void));

void* zmalloc(size_t size);
void* zrealloc(void* ptr, size_t len);
void* zcalloc(size_t count, size_t size);
void* zfmalloc(int fd, size_t size);
void zfree(void* ptr);
void zffree(void* fptr);

int zatoi(const char* arg);
long zatol(const char* arg);
double zatof(const char* arg);

int zitoa(int num, char* buf, const int base);
int zltoa(long num, char* buf, const int base);
int zlltoa(long long num, char* buf, const int base);
int zutoa(unsigned int num, char* buf, const int base);
int zultoa(unsigned long num, char* buf, const int base);
int zulltoa(unsigned long long num, char* buf, const int base);
int zztoa(size_t num, char* buf, const int base);
int zftoa(double num, char* buf, int presicion);

long zstrtol(const char* str, char** endptr, int base);
unsigned long zstrtoul(const char* str, char** endptr, int base);
double zstrtod(const char* str, char** endptr);

#endif /* Z_STDLIB_H */

