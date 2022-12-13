#include <zstdarg.h>
#include <zstdio.h>
#include <zstdlib.h>
#include <zstring.h>
#include <zctype.h>

int zvsscanf(const char* str, const char* fmt, va_list ap)
{
    int* n;
    char* s;
    float* f;
    int matches = 0;
    while (*fmt && *str) {
        if (*fmt == '%') {
            ++fmt;
            switch (*fmt) {
                case 'd': {
                    s = NULL;
                    n = va_arg(ap, int*);
                    *n = (int)zstrtol(str, &s, 10);
                    if (str != s) {
                        str += s - str - 1;
                    } else {
                        return matches;
                    }
                    break;
                }
                case 'c': {
                    while (_isspace(*str)) {
                        ++str;
                    }
                    
                    s = va_arg(ap, char*);
                    *s = *str++;
                    break;
                }
                case 's': {
                    while (_isspace(*str)) {
                        ++str;
                    }

                    s = va_arg(ap, char*);
                    while (_isgraph(*str)) {
                        *s++ = *str++;
                    }

                    ++str;
                    *s = 0;
                    break;
                }
                case 'f': {
                    s = NULL;
                    f = va_arg(ap, float*);
                    *f = (float)zstrtod(str, &s);
                    if (str != s) {
                        str += s - str - 1;
                    }
                    break;
                }
            }
            ++matches;
            ++fmt;
        }
        else if (_isspace(*fmt)) {
            while (_isspace(*str)) {
                ++str;
            }
            ++fmt;
        } 
        else if (*str != *fmt) {
            while (*str && *str != *fmt) {
                ++str;
            }
        } 
        else ++str, ++fmt;
    }
    return matches;
}

int zsscanf(const char* str, const char* fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = zvsscanf(str, fmt, ap);
    va_end(ap);
    return ret;
}

