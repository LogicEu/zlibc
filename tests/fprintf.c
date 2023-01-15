#include <zstdio.h>

int main(int argc, char** argv)
{
    int i;
    ZFILE* file;
    if (argc < 2) {
        zfprintf(zstderr, "Missing file name.\n");
        return 1;
    }

    file = zfopen(argv[1], "wb");
    if (!file) {
        zfprintf(zstderr, "Could not write file %s\n", argv[1]);
        return 2;
    }

    for (i = 0; i < 100; ++i) {
        zfprintf(file, "%d\n", i);
    }

    zfclose(file);
    return 0;
}
