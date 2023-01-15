#include <zsys.h>
#include <zstdarg.h>
#include <zstdlib.h>
#include <zstring.h>
#include <zstdio.h>

#define zinttoa(buf, base, l, ap) (!l ? zitoa(va_arg(ap, int), buf, base) : zltoa(va_arg(ap, long int), buf, base))
#define zuinttoa(buf, base, l, ap) (!l ? zutoa(va_arg(ap, unsigned int), buf, base) : zultoa(va_arg(ap, long unsigned int), buf, base))

static char stdio_buffer[BUFSIZ];

static size_t zioflush(int fd, size_t len)
{
    stdio_buffer[len] = 0;
    zwrite(fd, stdio_buffer, len);
    return len;
}

static const char* zstrfmt(const char* fmt, const char** end, size_t* len, va_list* ap)
{
    static char buf[BUFSIZ];
    
    size_t i = 0, l = (*fmt == 'l');
    fmt += l;
    
    switch (*fmt) {
        case '%': {
            buf[i++] = *fmt;
            break;
        }
        case 'c': {
            int c = va_arg(*ap, int);
            buf[i++] = c;
            break;
        }
        case 's': {
            const char* s = va_arg(*ap, char*);
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
            i += zinttoa(buf + i, 10, l, *ap);
            break;
        }
        case 'u': {
            i += zuinttoa(buf + i, 10, l, *ap);
            break;
        }
        case 'X': case 'x': {
            buf[i++] = '0';
            buf[i++] = 'x';
            i += zinttoa(buf + i, 16, l, *ap);
            break;
        }
        case 'b': {
            i += zinttoa(buf + i, 2, l, *ap);
            break;
        }
        case 'f': {
            double n = va_arg(*ap, double);
            i += zftoa(n, buf + i, 7);
            break;
        }
        case 'z': {
            size_t n = va_arg(*ap, size_t);
            i += zztoa(n, buf + i, 10);
            fmt += fmt[1] == 'u';
            break;
        }
        case 'p': {
            void* n = va_arg(*ap, void*);
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

int zvsprintf(char* buf, const char* fmt, va_list args)
{
    va_list ap;
    const char* arg;
    size_t i = 0, len;
    va_copy(ap, args);
    while (*fmt) {
        if (*fmt == '%') {
            arg = zstrfmt(++fmt, &fmt, &len, &ap);
            zmemcpy(buf + i, arg, len);
            i += len;
        }
        else buf[i++] = *fmt;
        ++fmt;
    }

    va_end(ap);
    buf[i] = 0;
    return i;
}

int zvsnprintf(char* buf, size_t size, const char* fmt, va_list args)
{
    va_list ap;
    const char* arg;
    size_t i = 0, len;
    va_copy(ap, args);
    while (*fmt && i + 1 >= BUFSIZ) {
        if (*fmt == '%') {
            arg = zstrfmt(++fmt, &fmt, &len, &ap);
            len = len + i > size ? size - len - 1 : len;
            zmemcpy(buf + i, arg, len);
            i += len;
        }
        else buf[i++] = *fmt;
        ++fmt;
    }

    va_end(ap);
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

int zvdprintf(int fd, const char* fmt, va_list args)
{
    va_list ap;
    const char* arg;
    size_t i = 0, len, ret = 0;
    va_copy(ap, args);
    while (*fmt) {
        if (*fmt == '%') {
            arg = zstrfmt(++fmt, &fmt, &len, &ap);
            if (i + len >= BUFSIZ) {
                ret += zioflush(fd, i);
                i = 0;
                if (*fmt == 's') {
                    zwrite(fd, arg, len);
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

    va_end(ap);
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

int zvfprintf(ZFILE* stream, const char* fmt, va_list ap)
{
    return zvdprintf(zfileno(stream), fmt, ap);
}

int zfprintf(ZFILE* stream, const char* fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = zvdprintf(zfileno(stream), fmt, ap);
    va_end(ap);
    return ret;
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
