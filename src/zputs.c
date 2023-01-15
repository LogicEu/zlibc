#include <zstdio.h>

int zfputs(const char* str, ZFILE* stream)
{
    const char* c = str, nl = '\n';
    while (*c) {
        if (!zfwrite(c++, sizeof(char), 1, stream)) {
            return ZEOF;
        }
    }
    return zfwrite(&nl, sizeof(char), 1, zstdout) ? 0 : ZEOF;
}

int zputs(const char* str)
{
    const char* c = str, nl = '\n';
    while (*c) {
        if (!zfwrite(c++, sizeof(char), 1, zstdout)) {
            return ZEOF;
        }
    }
    return zfwrite(&nl, sizeof(char), 1, zstdout) ? 0 : ZEOF;
}

