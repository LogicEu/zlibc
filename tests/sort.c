#include <zstdlib.h>
#include <zstdio.h>

int cmp(const void* a, const void* b)
{
    return *(long*)a - *(long*)b;
}

int main(const int argc, const char** argv)
{
    if (argc < 2) {
        zprintf("Missing size of array.\n");
        return Z_EXIT_FAILURE;
    }

    int i;
    const int size = zatoi(argv[1]);
    long* arr = zmalloc(sizeof(long) * size);

    zsrand(size);
    for (i = 0; i < size; ++i) {
        arr[i] = zrand() % size;
        zprintf("%d\n", arr[i]);
    }
    zprintf("\n");

    zqsort(arr, size, sizeof(long), &cmp);
    for (i = 0; i < size; ++i) {
        zprintf("%d\n", arr[i]);
    }

    zfree(arr);
    return Z_EXIT_SUCCESS;
}
