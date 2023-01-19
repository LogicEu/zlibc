#include <zsys.h>
#include <zstddef.h>

#ifndef Z_FOPEN_MAX
#define Z_FOPEN_MAX 20
#endif

#define Z_SEEK_SET 0
#define Z_SEEK_CUR 1
#define Z_SEEK_END 2

struct __zfile {
    int fileno;
};

typedef struct __zfile ZFILE;

static unsigned int __zopened_files = 0;
static ZFILE __zfile_buffer[Z_FOPEN_MAX];
static ZFILE __zstdin = {STDIN_FILENO};
static ZFILE __zstdout = {STDOUT_FILENO};
static ZFILE __zstderr = {STDERR_FILENO};

ZFILE* __zstdinp = &__zstdin;
ZFILE* __zstdoutp = &__zstdout;
ZFILE* __zstderrp = &__zstderr;

ZFILE* zfopen(const char* path, const char* modefmt)
{
    ZFILE* file;
    int fileno, flags;

    if (__zopened_files + 1 == Z_FOPEN_MAX) {
        return NULL;
    }

    switch (modefmt[0]) {
        case 'r':
            flags = modefmt[1] == '+' ? O_RDWR : O_RDONLY;
            break;
        case 'w':
            flags =  modefmt[1] == '+' ?
                    O_RDWR | O_CREAT | O_TRUNC :
                    O_WRONLY | O_CREAT | O_TRUNC;
            break;
        case 'a':
            flags =  modefmt[1] == '+' ?
                    O_RDWR | O_APPEND | O_CREAT :
                    O_WRONLY | O_APPEND | O_CREAT;
            break;
        default:
            return NULL;
    }

    fileno = zopen(path, flags, 0666);
    if (fileno <= STDERR_FILENO) {
        return NULL;
    }

    file = __zfile_buffer + __zopened_files++;
    file->fileno = fileno;
    return file;
}

int zfclose(ZFILE* stream)
{
    int fileno = stream->fileno;
    if (fileno <= STDERR_FILENO || !__zopened_files) {
        return -1;
    }

    stream->fileno = -1;
    --__zopened_files;
    return zclose(fileno);
}

int zfseek(ZFILE* stream, long offset, int whence)
{
    return zlseek(stream->fileno, offset, whence) == -1 ? -1 : 0;
}

void zrewind(ZFILE* stream)
{
    (void)zlseek(stream->fileno, 0, Z_SEEK_SET);
}

long zftell(ZFILE* stream)
{
    return (long)zlseek(stream->fileno, 0, Z_SEEK_CUR);
}

int zfileno(const ZFILE* stream)
{
    return stream ? stream->fileno : -1;
}

size_t zfread(void* ptr, size_t size, size_t count, ZFILE* stream)
{
    ssize_t offset = zread(stream->fileno, ptr, size * count);
    return offset < 0 ? 0 : (size_t)offset;
}

size_t zfwrite(const void* ptr, size_t size, size_t count, ZFILE* stream)
{
    ssize_t offset = zwrite(stream->fileno, ptr, size * count);
    return offset < 0 ? 0 : (size_t)offset;
}

