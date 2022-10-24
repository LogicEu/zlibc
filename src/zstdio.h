#ifndef Z_STDIO_H
#define Z_STDIO_H

#define stdin  0
#define stdout 1
#define stderr 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef void ZFILE;

#include <zstddef.h>
#include <stdarg.h>

int zputs(const char* str);
int zvfprintf(ZFILE* file, const char* fmt, va_list ap);
int zfprintf(ZFILE* file, const char* fmt, ...);
int zprintf(const char* fmt, ...);
ZFILE* zfopen(const char* path, const char* mode);
int zfclose(ZFILE* file);
size_t zfread(void* ptr, size_t size, size_t count, ZFILE* file);
size_t zwrite(void* ptr, size_t size, size_t count, ZFILE* file);
int zfseek(ZFILE* file, long offset, int whence);
long zftell(ZFILE* file);

#endif /* Z_STDIO_H */