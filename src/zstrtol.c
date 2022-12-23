#include <zstddef.h>
#include <zctype.h>

long zstrtol(const char* str, char** endptr, int base)
{
    long n = 0, sign = 1, i;

    while (_isspace(*str)) { 
        ++str; 
    }

    if (*str == '+') {
        ++str;
    }
    else if (*str == '-') {
        sign = -1;
        ++str;
    }

    if (base == 1 || base < 0) {
        goto zstrtolend;
    }
    else if (!base) {
        if (*str == '0') {
            base = 8;
            ++str;
            if (*str == 'x' || *str == 'X') {
                base = 16;
                ++str;
            }
            else if (*str == 'b' || *str == 'B') {
                base = 2;
                ++str;
            }
        }
        else if (*str > '0' && *str <= '9') {
            base = 10;
        }
        else goto zstrtolend;
    }

    while (*str) {
        i = _isupper(_toupper(*str)) * (*str - 'A' + 11) 
            + _isdigit(*str) * (*str - '0' + 1);
        ++str;
        if (!i || i > base) {
            break;
        }
        n = n * base + i - 1;
    }

zstrtolend:
    if (endptr) {
        *endptr = (char*)(size_t)str;
    }

    return sign * n;
}

unsigned long zstrtoul(const char* str, char** endptr, int base)
{
    long n = 0, sign = 1, i;
    while (_isspace(*str)) { 
        ++str; 
    }

    if (*str == '+') {
        ++str;
    }
    else if (*str == '-') {
        sign = -1;
        ++str;
    }

    if (base == 1 || base < 0) {
        goto zstrtoulend;
    }
    else if (!base) {
        if (*str == '0') {
            base = 8;
            ++str;
            if (*str == 'x' || *str == 'X') {
                base = 16;
                ++str;
            }
            else if (*str == 'b' || *str == 'B') {
                base = 2;
                ++str;
            }
        }
        else if (*str > '0' && *str <= '9') {
            base = 10;
        }
        else goto zstrtoulend;
    }

    while (*str) {
        i = _isupper(_toupper(*str)) * (*str - 'A' + 11) 
            + _isdigit(*str) * (*str - '0' + 1);
        ++str;
        if (!i || i > base) {
            break;
        }
        n = n * base + i - 1;
    }

zstrtoulend:
    if (endptr) {
        *endptr = (char*)(size_t)str;
    }

    return (unsigned long)(sign * n);
}

double zstrtod(const char* str, char** endptr) 
{
    int dot = 0;
    double n = 0.0, sign = 1.0, f;

    while (_isspace(*str)) { 
        ++str; 
    }

    if (*str == '+') {
        ++str;
    }
    else if (*str == '-') {
        sign = -1.0;
        ++str;
    }
    else if (*str == '.') {
        ++dot;
        ++str;
    } 

    while (_isdigit(*str)) {
        f = (double)(*str++ - '0');
        if (!dot) {
            n = n * 10.0 + f;
            if (*str == '.') {
                ++dot;
                ++str;
            }
        }
        else {
            dot *= 10;
            n += f / (double)dot;
        }
    }

    if (endptr) {
        *endptr = (char*)(size_t)str;
    }

    return n * sign;
}

