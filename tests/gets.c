#include <zstdio.h>

#define SIZE 256

int main(int argc, char** argv)
{
    ZFILE* file;
    int size = SIZE;
    char buf[SIZE];

    if (argc < 2) {
        zprintf("Missing input file.\n");
        return 1;
    }

    file = zfopen(argv[1], "rb");
    if (!file) {
        zprintf("Could not open file %s\n", argv[1]);
        return 1;
    }

    while ((zfgets(buf, size, file))) {
        zprintf("%s", buf); 
    }
    
    zfclose(file);
    return 0;
}

