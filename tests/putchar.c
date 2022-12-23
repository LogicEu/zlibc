#include <zstdio.h>

static void printstr(const char* str)
{
    size_t i;
    zputchar('\'');
    for (i = 0; str[i]; ++i) {
        zputchar(str[i]);
    }
    zputchar('\'');
}

int main(int argc, char** argv)
{
    int i;
    for (i = 0; i < argc; ++i) {
        printstr(argv[i]);
    }
    zputchar('\n');
    return 0;
}
