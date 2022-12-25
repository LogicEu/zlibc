#include <zstdio.h>
#include <zstdlib.h>

int main(void)
{
    static const char* hey = "Hey";
    int* n = zmalloc(sizeof(int));
    *n = 10;
    zprintf("%s\n%p\n", NULL, NULL);
    zprintf("%zu\n", sizeof(n));
    zprintf("String: %s\nStack Ptr: %p\nHeap Ptr: %p\nsize_t: %zu\nint: %d\n",
            hey, (void*)&n, (void*)n, sizeof(n), *n);
    zprintf("Stack Ptr: %p\n", &n);
    zprintf("Heap Ptr: %p\n", n);
    zprintf("%d\n", *n);
    zprintf("%p\n", n);
    zprintf("'%s', '%s'\n", "", NULL);
    zprintf("'%s', '%s'\n", NULL, "Yow");
    zprintf("%p\n", hey);
    zfree(n);
    return Z_EXIT_SUCCESS;
}
