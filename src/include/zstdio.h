#ifndef Z_STDIO_H
#define Z_STDIO_H

#include <sys/types.h>
#include <zstddef.h>

#define ZBUFSIZ 1024
#define ZEOF (-1)

#ifndef BUFSIZ
#define BUFSIZ ZBUFSIZ
#endif

#ifndef EOF
#define EOF ZEOF
#endif

#define	Z_SEEK_SET 0
#define	Z_SEEK_CUR 1
#define	Z_SEEK_END 2

#define	Z_FOPEN_MAX 20
#define	Z_FILENAME_MAX 1024

typedef struct __zfile ZFILE;

extern ZFILE* __zstdinp;
extern ZFILE* __zstdoutp;
extern ZFILE* __zstderrp;

#define zstdin __zstdinp
#define zstdout __zstdoutp
#define zstderr __zstderrp

ZFILE* zfopen(const char* path, const char* modefmt);
int zfclose(ZFILE* stream);
int zfileno(const ZFILE* stream);
int zfseek(ZFILE* stream, long offset, int whence);
long zftell(ZFILE* stream);
void zrewind(ZFILE* stream);
size_t zfread(void* ptr, size_t size, size_t count, ZFILE* stream);
size_t zfwrite(const void* ptr, size_t size, size_t count, ZFILE* stream);

int zsnprintf(char* buf, size_t size, const char* fmt, ...);
int zsprintf(char* buf, const char* fmt, ...);
int zdprintf(int fd, const char* fmt, ...);
int zprintf(const char* fmt, ...);

int zputc(int c, int fd);
int zputchar(int c);

int zgetc(int fd);
int zgetchar(void);

ssize_t zgetdelim(char** linep, size_t* linecap, int delim, int fd);
ssize_t zgetline(char** linep, size_t* linecap, int fd);

int zsscanf(const char* str, const char* fmt, ...);

void zperror(const char* s);

#endif /* Z_STDIO_H */
