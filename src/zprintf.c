#include <zsys.h>
#include <zstdarg.h>
#include <zstdlib.h>
#include <zstring.h>
#include <zstdio.h>

static char stdio_buffer[BUFSIZ];

static int zsysprint(const char* str, int fd, int len)
{
    return zwrite(fd, str, len);
}

static size_t zioflush(int fd, size_t len)
{
    stdio_buffer[len] = 0;
    zsysprint(stdio_buffer, fd, len);
    return len;
}

#define lli(buf, i, base, l, ap, type) do {                     \
    switch(l) {                                                 \
        case 0: {                                               \
            i += zitoa(va_arg(ap, type), buf + i, base);        \
            break;                                              \
        }                                                       \
        case 1: {                                               \
            i += zltoa(va_arg(ap, long type), buf + i, base);   \
            break;                                              \
        }                                                       \
    }                                                           \
} while (0)

#define llu(buf, i, base, l, ap, type) do {                     \
    switch(l) {                                                 \
        case 0:                                                 \
            i += zutoa(va_arg(ap, type), buf + i, base);        \
            break;                                              \
        case 1:                                                 \
            i += zultoa(va_arg(ap, long type), buf + i, base);  \
            break;                                              \
    }                                                           \
} while (0)

static const char* zstrfmt(const char* fmt, const char** end, size_t* len, va_list ap)
{
    static char buf[BUFSIZ];
    
    size_t l, i = 0;
    for (l = 0; *fmt == 'l' && l < 1; ++l) {
        ++fmt;
    }
    
    switch (*fmt) {
        case '%': {
            buf[i++] = *fmt;
            break;
        }
        case 'c': {
            int c = va_arg(ap, int);
            buf[i++] = c;
            break;
        }
        case 's': {
            const char* s = va_arg(ap, char*);
            *end = fmt;
            if (!s) {
                static const char nullstr[] = "(null)";
                *len = sizeof(nullstr);
                return nullstr;
            }
            *len = i + zstrlen(s);
            return s;
        }
        case 'd': {
            lli(buf, i, 10, l, ap, int);
            break;
        }
        case 'u': {
            llu(buf, i, 10, l, ap, unsigned int);
            break;
        }
        case 'X':
        case 'x': {
            buf[i++] = '0';
            buf[i++] = 'x';
            lli(buf, i, 16, l, ap, int);
            break;
        }
        case 'b': {
            lli(buf, i, 2, l, ap, int);
            break;
        }
        case 'f': {
            double n = va_arg(ap, double);
            i += zftoa(n, buf + i, 7);
            break;
        }
        case 'z': {
            size_t n = va_arg(ap, size_t);
            i += zztoa(n, buf + i, 10);
            fmt += fmt[1] == 'u';
            break;
        }
        case 'p': {
            void* n = va_arg(ap, void*);
            buf[i++] = '0';
            buf[i++] = 'x';
            i += zztoa((size_t)n, buf + i, 16);
            break;
        }
    }

    buf[i] = 0;
    *len = i;
    *end = fmt;

    return buf;
}

int zvsprintf(char* buf, const char* fmt, va_list ap)
{
    const char* arg;
    size_t i = 0, len;
    while (*fmt) {
        if (*fmt == '%') {
            arg = zstrfmt(++fmt, &fmt, &len, ap);
            zmemcpy(buf + i, arg, len);
            i += len;
        }
        else buf[i++] = *fmt;
        ++fmt;
    }
    
    buf[i] = 0;
    return i;
}

int zvsnprintf(char* buf, size_t size, const char* fmt, va_list ap)
{
    const char* arg;
    size_t i = 0, len;
    while (*fmt && i + 1 >= BUFSIZ) {
        if (*fmt == '%') {
            arg = zstrfmt(++fmt, &fmt, &len, ap);
            len = len + i > size ? size - len - 1 : len;
            zmemcpy(buf + i, arg, len);
            i += len;
        }
        else buf[i++] = *fmt;
        ++fmt;
    }
    
    buf[i] = 0;
    return i;
}

int zsnprintf(char* buf, size_t size, const char* fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = zvsnprintf(buf, size, fmt, ap);
    va_end(ap);
    return ret;
}

int zsprintf(char* buf, const char* fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = zvsprintf(buf, fmt, ap);
    va_end(ap);
    return ret;
}

int zvdprintf(int fd, const char* fmt, va_list ap)
{
    const char* arg;
    size_t i = 0, len, ret = 0;
    while (*fmt) {
        if (*fmt == '%') {
            arg = zstrfmt(++fmt, &fmt, &len, ap);
            if (i + len >= BUFSIZ) {
                ret += zioflush(fd, i);
                i = 0;
                if (*fmt == 's') {
                    zsysprint(arg, fd, len);
                    ++fmt;
                    continue;
                }
            }
            zmemcpy(stdio_buffer + i, arg, len);
            i += len;
        }
        else stdio_buffer[i++] = *fmt;
        ++fmt;

        if (i + 1 >= BUFSIZ) {
            ret += zioflush(fd, i);
            i = 0;
        }
    }
    
    ret += zioflush(fd, i);
    return ret;
}

int zdprintf(int fd, const char* fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = zvdprintf(fd, fmt, ap);
    va_end(ap);
    return ret;
}

int zvprintf(const char* fmt, va_list ap)
{
    return zvdprintf(STDOUT_FILENO, fmt, ap);
}

int zprintf(const char* fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = zvdprintf(STDOUT_FILENO, fmt, ap);
    va_end(ap);
    return ret;
}
