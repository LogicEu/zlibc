#include <zsys.h>
#include <zstdio.h>
#include <zstdlib.h>

#define Z_GETDELIM_BUFSIZ 8

ssize_t zgetdelim(char** linep, size_t* linecap, int delim, int fd)
{
    signed char c;
    ssize_t out = 0;

    if (!linep[0]) {
        linep[0] = zmalloc(Z_GETDELIM_BUFSIZ);
        *linecap = Z_GETDELIM_BUFSIZ;
    }

    do {
        
        zread(fd, &c, 1);
        if (c == Z_EOF) {
            return -1;
        }

        if (out + 1 >= (ssize_t)*linecap) {
            *linecap <<= 1;
            linep[0] = zrealloc(linep[0], *linecap);
        }

        linep[0][out++] = c;
    } while (c != delim && c != 0);

    linep[0][out] = 0;
    return out;
}

ssize_t zgetline(char** linep, size_t* linecap, int fd)
{
    return zgetdelim(linep, linecap, '\n', fd);
}
