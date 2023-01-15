#include <zstdio.h>

int zfputc(int c, ZFILE* stream)
{
    unsigned char ch =  (unsigned char)c;
    size_t err = zfwrite(&ch, sizeof(unsigned char), 1, stream);
    return !err ? ZEOF : c;
}

int zputc(int c, ZFILE* stream)
{
    unsigned char ch = (unsigned char)c;
    size_t err = zfwrite(&ch, sizeof(unsigned char), 1, stream);
    return !err ? ZEOF : c;
}

int zputchar(int c)
{ 
    unsigned char ch = (unsigned char)c;
    size_t err = zfwrite(&ch, sizeof(unsigned char), 1, zstdout);
    return !err ? ZEOF : c;
}

