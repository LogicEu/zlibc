#ifndef Z_STDIO_H
#define Z_STDIO_H

#include <zstdarg.h>

#define BUFSIZ 1024

int zprintf(const char* str, ...);
int zvsprintf(char* buf, const char* fmt, va_list ap);
int zsprintf(char* buf, const char* fmt, ...);
int zvprintf(const char* fmt, va_list ap);

#endif /* Z_STDIO_H */
