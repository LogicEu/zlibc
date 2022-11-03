#include <zstring.h>

void* zmemcpy(void* dst, const void* src, size_t n)
{
    unsigned char* a = dst;
    const unsigned char* b = src;
    while (n--) {
        *a++ = *b++;
    }
    return dst;
}

void* zmemmove(void* dst, const void* src, size_t n)
{
    unsigned char* a = dst;
    const unsigned char* b = src;
    if (a < b) {
        while (n--) {
            *a++ = *b++;
        }
    } else {
        while (n--) {
            a[n] = b[n];
        }
    }
    return dst;
}

int zmemcmp(const void* p1, const void* p2, size_t n)
{
    const unsigned char* a = p1, *b = p2;
    while (n && *a == *b) {
        ++a, ++b, --n;
    }
    return n ? (*a - *b) : 0;
}

void* zmemset (void* dst, int val, size_t n)
{
    unsigned char* a = dst;
    while (n--) {
        *a++ = val;
    }
    return dst;
}

char* zstrcpy(char* dst, const char* src)
{
    unsigned char* a = (unsigned char*)dst;
    const unsigned char* b = (unsigned char*)src;
    while (*b) {
        *a++ = *b++;
    }
    *a = 0;
    return dst;
}

char* zstrcat(char* dst, const char* src)
{
    unsigned char* a = (unsigned char*)dst;
    const unsigned char* b = (unsigned char*)src;
    while (*a) {
        ++a;
    }

    while (*b) {
        *a++ = *b++;
    }
    
    *a = 0;
    return dst;
}

int zstrcmp(const char* s1, const char* s2)
{
    const unsigned char* a = (unsigned char*)s1;
    const unsigned char* b = (unsigned char*)s2;
    while (*a && *a == *b) {
        ++a, ++b;
    }
    return *a - *b;
}

size_t zstrlen(const char* str)
{
    size_t i;
    for (i = 0; str[i]; ++i);
    return i;
}

char* zstrchr(const char* str, const int c)
{
    while (*str) {
        if (*str == c) {
            return (char*)(size_t)str;
        } 
        ++str;
    }
    return NULL;
}

char* zstrstr(const char* big, const char* small)
{
    const size_t len = zstrlen(small);
    while (*big) {
        if (!zmemcmp(big, small, len)) {
            return (char*)(size_t)big;
        }
        ++big;
    }
    return NULL;
}

char* zstrrev(char* str)
{
    size_t len = zstrlen(str), i = 0;
    while (i < len) {
        char c = str[i];
        str[i++] = str[len - 1];
        str[--len] = c;
    }
    return str;
}

char* zstrnrev(char* str, size_t len)
{
    size_t i = 0;
    while (i < len) {
        char c = str[i];
        str[i++] = str[len - 1];
        str[--len] = c;
    }
    return str;
}
