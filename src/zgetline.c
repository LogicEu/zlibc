#include <zstdio.h>
#include <zstdlib.h>

#define Z_GETDELIM_BUFSIZ 32

ssize_t zgetdelim(char** linep, size_t* linecap, int delim, ZFILE* stream)
{
    signed char c;
    ssize_t out = 0;

    if (!linep[0]) {
        linep[0] = zmalloc(Z_GETDELIM_BUFSIZ);
        *linecap = Z_GETDELIM_BUFSIZ;
    }

    do {
        size_t err = zfread(&c, sizeof(signed char), 1, stream); 
        if (out + 1 >= (ssize_t)*linecap) {
            *linecap <<= 1;
            linep[0] = zrealloc(linep[0], *linecap);
        }
        
        if (!err || c == ZEOF) {
            linep[0][out] = 0;
            return ZEOF;
        }

        linep[0][out++] = c;
    } while (c != delim && c != 0);

    linep[0][out] = 0;
    return out;
}

ssize_t zgetline(char** linep, size_t* linecap, ZFILE* stream)
{
    signed char c;
    ssize_t out = 0;

    if (!linep[0]) {
        linep[0] = zmalloc(Z_GETDELIM_BUFSIZ);
        *linecap = Z_GETDELIM_BUFSIZ;
    }

    do {
        size_t err = zfread(&c, sizeof(signed char), 1, stream); 
        if (out + 1 >= (ssize_t)*linecap) {
            *linecap <<= 1;
            linep[0] = zrealloc(linep[0], *linecap);
        }
        
        if (!err || c == ZEOF) {
            linep[0][out] = 0;
            return ZEOF;
        }

        linep[0][out++] = c;
    } while (c != '\n' && c != 0);

    linep[0][out] = 0;
    return out;
}

