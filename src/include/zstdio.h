#ifndef Z_STDIO_H
#define Z_STDIO_H

#include <zsys.h>
#include <zstddef.h>

#define BUFSIZ 1024
#define EOF (-1)

int zsnprintf(char* buf, size_t size, const char* fmt, ...);
int zsprintf(char* buf, const char* fmt, ...);
int zdprintf(int fd, const char* fmt, ...);
int zprintf(const char* fmt, ...);

int zsscanf(const char* str, const char* fmt, ...);

ssize_t zgetdelim(char** linep, size_t* linecap, int delim, int fd);
ssize_t zgetline(char** linep, size_t* linecap, int fd);

#endif /* Z_STDIO_H */
