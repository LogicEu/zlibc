#include <zstdio.h>

int zgetc(ZFILE* stream)
{
    int c;
    size_t err = zfread(&c, sizeof(char), 1, stream);
    return !err ? ZEOF : c;
}

int zgetchar(void)
{ 
    int c;
    size_t err = zfread(&c, sizeof(char), 1, zstdin);
    return !err ? ZEOF : c;
}
