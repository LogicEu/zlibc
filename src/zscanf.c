#include <zstdarg.h>
#include <zstdio.h>
#include <zstdlib.h>
#include <zstring.h>
#include <zctype.h>

int zvsscanf(const char* str, const char* fmt, va_list ap)
{
    int matches = 0;
    while (*fmt && *str) {
        if (*fmt == '%') {
            ++fmt;
            switch (*fmt) {
                case 'd': {
                    char* end = NULL;
                    int* n = va_arg(ap, int*);
                    *n = (int)zstrtol(str, &end, 10);
                    if (str != end) {
                        str += end - str - 1;
                    } else {
                        return matches;
                    }
                    break;
                }
                case 'c': {
                    while (_isspace(*str)) {
                        ++str;
                    }
                    
                    char* c = va_arg(ap, char*);
                    *c = *str++;
                    break;
                }
                case 's': {
                    while (_isspace(*str)) {
                        ++str;
                    }

                    char* s = va_arg(ap, char*);
                    while (_isgraph(*str)) {
                        *s++ = *str++;
                    }

                    ++str;
                    *s = 0;
                    break;
                }
                case 'f': {
                    char* end = NULL;
                    float* n = va_arg(ap, float*);
                    *n = (float)zstrtod(str, &end);
                    if (str != end) {
                        str += end - str - 1;
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
    va_list ap;
    va_start(ap, fmt);
    int ret = zvsscanf(str, fmt, ap);
    va_end(ap);
    return ret;
}