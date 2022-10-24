#include <zstdio.h>
#include <zsys.h>
#include <zstring.h>

int zputs(const char* str)
{
    static char buf[0xffff];
    size_t len = zstrlen(str);
    zmemcpy(buf, str, len);
    buf[len++] = '\n';
    buf[len] = 0;
    zsyscall(SYS_write, stdout, buf, len);
    return 0;
}

#include <stdio.h>

int zvfprintf(ZFILE* file, const char* fmt, va_list ap)
{
    return vfprintf(file, fmt, ap);
}

int zfprintf(ZFILE* file, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int ret = zvfprintf(file, fmt, args);
    va_end(args);
    return ret;
}

int zprintf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int ret = zvfprintf(stdout, fmt, args);
    va_end(args);
    return ret;
}

ZFILE* zfopen(const char* path, const char* mode)
{
    return fopen(path, mode);
}

int zfclose(ZFILE* file)
{
    return fclose(file);
}

size_t zfread(void* ptr, size_t size, size_t count, ZFILE* file)
{
    return fread(ptr, size, count, file);
}

size_t zfwrite(void* ptr, size_t size, size_t count, ZFILE* file)
{
    return fwrite(ptr, size, count, file);
}

int zfseek(ZFILE* file, long offset, int whence)
{
    return fseek(file, offset, whence);
}

long zftell(ZFILE* file)
{
    return ftell(file);
}