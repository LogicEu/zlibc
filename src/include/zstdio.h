#ifndef Z_STDIO_H
#define Z_STDIO_H

#include <zsys.h>
#include <zstddef.h>

#define BUFSIZ 1024

#ifndef __ZEOF
    #define __ZEOF
    #define ZEOF (-1)
    #ifndef EOF
        #define EOF ZNULL
    #endif
#endif /* EOF */

int zsnprintf(char* buf, size_t size, const char* fmt, ...);
int zsprintf(char* buf, const char* fmt, ...);
int zdprintf(int fd, const char* fmt, ...);
int zprintf(const char* fmt, ...);

int zputc(int c, int fd);
int zputchar(int c);

int zsscanf(const char* str, const char* fmt, ...);

int zgetc(int fd)
int zgetchar(void)

ssize_t zgetdelim(char** linep, size_t* linecap, int delim, int fd);
ssize_t zgetline(char** linep, size_t* linecap, int fd);

#endif /* Z_STDIO_H */
