#ifndef Z_STDIO_H
#define Z_STDIO_H

#include <sys/types.h>
#include <zstddef.h>

#ifndef BUFSIZ 
#define BUFSIZ 1024
#endif

#ifndef Z_SEEK_SET
#define	Z_SEEK_SET 0
#endif

#ifndef Z_SEEK_CUR
#define	Z_SEEK_CUR 1
#endif

#ifndef Z_SEEK_END
#define	Z_SEEK_END 2
#endif

#ifndef ZEOF
#define ZEOF (-1)
#ifndef EOF
#define EOF ZEOF
#endif
#endif

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

#endif /* Z_STDIO_H */
