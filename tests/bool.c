#include <zstdbool.h>
#include <zstdio.h>

int main(void)
{
    bool a;
    a = true;
    zprintf("%d\n", a);
    a = false;
    zprintf("%d\n", a);
    zprintf("%zu\n", sizeof(bool));
    return 0;
}
