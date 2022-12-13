#include <zstdio.h>
#include <zstdlib.h>

int main(int argc, char** argv)
{
    if (argc < 3) {
        zprintf("Missing input nums\n");
        return Z_EXIT_FAILURE;
    }
    zprintf("\033[%dC", zatoi(argv[1]));
    zprintf("\033[%dB", zatoi(argv[2]));
    zprintf("Hey\n");
    return Z_EXIT_SUCCESS;
}
