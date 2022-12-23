#include <zstddef.h>
#include <zlimits.h>

#define swap(a, b, size)            \
do {                                \
    size_t __size = (size);         \
    char *__a = (a), *__b = (b);    \
    do {                            \
        char __tmp = *__a;          \
        *__a++ = *__b;              \
        *__b++ = __tmp;             \
    } while (--__size > 0);         \
} while (0)

static size_t zqpartition(
    void* arr, const size_t bytes, const size_t low, const size_t high, 
    int (*cmpfunc)(const void*, const void*))
{
    size_t i = low - 1, j;
    const void* pivot = (char*)arr + high * bytes;
    for (j = low; j < high; ++j) {
        if (cmpfunc((char*)arr + j * bytes, pivot) < 0) {
            swap((char*)arr + (++i) * bytes, (char*)arr + j * bytes, bytes);
        }
    }
    swap((char*)arr + (++i) * bytes, (char*)arr + high * bytes, bytes);
    return i;
}

static void zquicksort(
    void* arr, const size_t bytes, const size_t low, const size_t high,
    int (*cmpfunc)(const void*, const void*))
{
    if (low < high && high != Z_SIZE_MAX) {
        const size_t p = zqpartition(arr, bytes, low, high, cmpfunc);
        zquicksort(arr, bytes, low, p - 1, cmpfunc);
        zquicksort(arr, bytes, p + 1, high, cmpfunc);
    }
}

void zqsort(
    void* base, size_t count, size_t bytes, 
    int (*cmpfunc)(const void*, const void*))
{
    zquicksort(base, bytes, 0, count - 1, cmpfunc);
}
