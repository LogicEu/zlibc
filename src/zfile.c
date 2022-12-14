#include <zsys.h>
#include <zstddef.h>

extern void* zmalloc(size_t);
extern void zfree(void*);

typedef struct __zfile ZFILE;

struct __zfile {
    int flags;
    int fileno;
    off_t offset;
    size_t size;
};

static struct __zfile __zstdin = {O_RDONLY, STDIN_FILENO, 0, 0};
static struct __zfile __zstdout = {O_WRONLY, STDOUT_FILENO, 0, 0};
static struct __zfile __zstderr = {O_WRONLY, STDERR_FILENO, 0, 0};

ZFILE* __zstdinp = &__zstdin;
ZFILE* __zstdoutp = &__zstdout;
ZFILE* __zstderrp = &__zstderr;

ZFILE* zfopen(const char* path, const char* modefmt)
{
    int fileno, flags;
    struct stat st;
    struct __zfile* file;

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
    if (fileno < 0 || zfstat(fileno, &st) < 0) {
        return NULL;
    }
    
    file = zmalloc(sizeof(struct __zfile));
    if (!file) {
        return NULL;
    }

    file->flags = flags;
    file->fileno = fileno;
    file->size = modefmt[0] == 'w' ? 0 : (size_t)st.st_size;
    file->offset = modefmt[0] == 'a' ? (off_t)st.st_size : 0;

    return file;
}

int zfclose(ZFILE* stream)
{
    int fileno = stream->fileno;
    zfree(stream);
    return zclose(fileno);
}

int zfseek(ZFILE* stream, long offset, int whence)
{
    off_t off = zlseek(stream->fileno, offset, whence);
    if (off == -1) {
        return -1;
    }

    stream->offset = off;
    return 0;
}

void zrewind(ZFILE* stream)
{
    off_t off = zlseek(stream->fileno, 0, 0);
    if (off != -1) {
        stream->offset = off;
    }
}

long zftell(ZFILE* stream)
{
    return (long)stream->offset;
}

int zfileno(const ZFILE* stream)
{
    return stream ? stream->fileno : -1;
}

size_t zfread(void* ptr, size_t size, size_t count, ZFILE* stream)
{
    ssize_t offset = zread(stream->fileno, ptr, size * count);
    if (offset < 0) {
        return 0;
    }
    
    stream->offset += offset;
    return (size_t)offset;
}

size_t zfwrite(const void* ptr, size_t size, size_t count, ZFILE* stream)
{
    ssize_t offset;
    offset = zwrite(stream->fileno, ptr, size * count);
    if (offset < 0) {
        return 0;
    }

    stream->offset += offset;
    stream->size += offset;
    return (size_t)offset;
}
