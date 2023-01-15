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

#ifndef ZFILE_DEFINED
#define ZFILE_DEFINED
typedef struct __zfile ZFILE;
#endif

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
int zfprintf(ZFILE* stream, const char* fmt, ...);
int zprintf(const char* fmt, ...);

int zputc(int c, ZFILE* stream);
int zfputc(int c, ZFILE* stream);
int zputchar(int c);

int zfputs(const char* str, ZFILE* stream);
int zputs(const char* str);

int zgetc(ZFILE* stream);
int zgetchar(void);

char* zfgets(char* str, int size, ZFILE* stream);
char* zgets(char* str);

ssize_t zgetdelim(char** linep, size_t* linecap, int delim, ZFILE* stream);
ssize_t zgetline(char** linep, size_t* linecap, ZFILE* stream);

int zsscanf(const char* str, const char* fmt, ...);

void zperror(const char* s);

#endif /* Z_STDIO_H */
