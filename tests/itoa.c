#include <zstdlib.h>
#include <zstdio.h>

int main(void)
{
    char buf[0xff];
    int n = 100841;
    zitoa(n, buf, 16);
    zprintf("%x\n", n);
    zputs(buf);

    n = -10;
    zitoa(n, buf, 16);
    zprintf("%x\n", n);
    zputs(buf);
    
    return Z_EXIT_SUCCESS;
}
