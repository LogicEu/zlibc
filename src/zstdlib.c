#include <zstdlib.h>
#include <zsys.h>
#include <zstring.h>

extern void* malloc(size_t size);
extern void free(void* data);

void* zmalloc(size_t size)
{
    return malloc(size);
}

void zfree(void* ptr)
{
    return free(ptr);
}

void zexit(int status)
{
    zsyscall(SYS_exit, status);
}

int zatoi(const char* str)
{
    int i, j = 1, n = 0, neg = (str[0] == '-');
    for (i = neg; str[i] >= '0' && str[i] <= '9'; ++i);
    for (--i; i >= neg; --i) {
        n += (str[i] - '0') * j;
        j *= 10;
    }
    return neg ? -n : n;
}

long zatol(const char* str)
{
    long i, j = 1, n = 0, neg = (str[0] == '-');
    for (i = 0; str[i] >= '0' && str[i] <= '9'; ++i);
    for (--i; i >= neg; --i) {
        n += (str[i] - '0') * j;
        j *= 10;
    }
    return neg ? -n : n;
}

int zitoa(int num, char* str, const int base)
{
    int i = 0, neg = 0;
    if (!num) {
        str[i++] = '0';
        str[i] = 0;
        return i;
    }
 
    if (num < 0 && base == 10) {
        ++neg;
        num = -num;
    }
 
    while (num) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    if (neg) {
        str[i++] = '-';
    }
 
    str[i] = 0;
    zstrrev(str);
    return i;
}

long zstrtol(const char* str, char** endptr, int base)
{
    long sign = 1;
    if (*str == '+') {
        ++str;
    }
    else if (*str == '-') {
        sign = -1;
        ++str;
    }

    if (base == 1 || base < 0) {
        return 0;
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
        else return 0;
    }

    long n = 0, i;
    while (*str) {
        i =   (*str >= 'a' && *str <= 'z') * (*str - 'a' + 11)
            + (*str >= 'A' && *str <= 'Z') * (*str - 'A' + 11)
            + (*str >= '0' && *str <= '9') * (*str - '0' + 01);
        ++str;
        if (!i || i > base) {
            break;
        }
        n = n * base + i - 1;
    }

    if (endptr) {
        *endptr = (char*)(size_t)str;
    }

    return sign * n;
}