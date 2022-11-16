#include <zstdio.h>
#include <zstdlib.h>
#include <zsys.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        zprintf("Missing input file.\n");
        return 1;
    }
 
    char* fpath = argv[1];
    int fd = zopen(fpath, O_RDONLY);
    if (fd != -1) {
        zprintf("FD: %d\n", fd);
        struct stat s;
        zfstat(fd, &s);
        size_t size = (size_t)s.st_size;
        zprintf("Size: %zu\n", size);
        void* f = zfmalloc(fd, size);
        if (f) {
            zprintf("%s\n", f);
            zfree(f);
        }
        zclose(fd);
    }

    return 0;
}
