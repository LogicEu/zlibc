#include <zstdlib.h>
#include <zstdio.h>
int main(const int argc, const char** argv)
{
    if (argc < 2) {
        zprintf("Missing input seed.\n");
        return Z_EXIT_FAILURE;
    }
    int i;
    zsrand(zatoi(argv[1]));
    for (i = 0; i < 100; ++i) {
        zprintf("%d\n", zrand());
    }
    return Z_EXIT_SUCCESS;
}
