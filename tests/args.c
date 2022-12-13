#include <zstdio.h>
#include <zstdlib.h>

int main(int argc, char** argv, char** envp)
{
    int i;
    zprintf("%d\n", argc);
    for (i = 0; i < argc; ++i) {
        zprintf("%s\n", argv[i]);
    }
    for (i = 0; envp[i]; ++i) {
        zprintf("%s\n", envp[i]);
    }
    return Z_EXIT_SUCCESS;
}
