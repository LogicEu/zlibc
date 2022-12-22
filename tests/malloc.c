#include <zstdlib.h>
#include <zstdio.h>
#define SIZE 1000

static int* sqget(const int N) 
{
    int* n = zmalloc(sizeof(int) * N), i;
    for (i = 0; i < N; ++i) {
        n[i] = i * i;
    }
    return n;
}

static void sqprnt(const int* arr, const int N)
{
    int i;
    for (i = 0; i < N; ++i) {
        zprintf("%d\n", arr[i]);
    }
}

static void prnt(void)
{
    zprintf("The End!\n");
}

int main(void)
{
    const int N = SIZE;
    int* n = sqget(N);
    zatexit(&prnt);
    if (!n) {
        zprintf("Could not alloc.\n");
        return Z_EXIT_FAILURE;
    }
    sqprnt(n, N);
    zfree(n);
    return Z_EXIT_SUCCESS;
}
