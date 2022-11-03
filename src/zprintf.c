#include <zsys.h>
#include <zstddef.h>
#include <zstdlib.h>
#include <zstring.h>
#include <zstdio.h>

static char stdio_buffer[BUFSIZ];

static int zsysprint(const char* str, int len)
{
    return zsyscall(SYS_write, SYS_STDOUT, str, len);
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
        case 2: {                                               \
            i += zlltoa(va_arg(ap, long long type), buf + i, base);\
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
        case 2:                                                 \
            i += zulltoa(va_arg(ap, long long type), buf + i, base);\
    }                                                           \
} while (0)

static char* zstrfmt(const char* fmt, const char** end, int* len, va_list ap)
{
    static char buf[BUFSIZ];
    
    int l, i = 0;
    for (l = 0; *fmt == 'l' && l < 2; ++l) {
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
            char* s = va_arg(ap, char*);
            int len = zstrlen(s);
            zmemcpy(buf + i, s, len);
            i += len;
            break;
        }
        case 'd': {
            lli(buf, i, 10, l, ap, int);
            break;
        }
        case 'u': {
            llu(buf, i, 10, l, ap, unsigned int);
            break;
        }
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
            buf[i++] = '0';
            buf[i++] = 'x';
            void* n = va_arg(ap, void*);
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
    char* arg;
    int i = 0, len;
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

int zsprintf(char* buf, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = zvsprintf(buf, fmt, ap);
    va_end(ap);
    return ret;
}

int zvprintf(const char* fmt, va_list ap)
{
    int ret = zvsprintf(stdio_buffer, fmt, ap);
    zsysprint(stdio_buffer, ret);
    return ret;
}

int zprintf(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = zvprintf(fmt, ap);
    va_end(ap);
    return ret;
}