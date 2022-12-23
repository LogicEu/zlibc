#include <zstdio.h>

int main(void)
{
    int c;
    while (1) {
        c = zgetchar();
        zputchar(c);
        zputchar('\n');
    }
    return 0;
}
