#include <zstdio.h>

int main(void)
{
    zputs("puts: Hello World!");
    zfputs("fputs (stderr): Hello World!", zstderr);
    return 0;
}
