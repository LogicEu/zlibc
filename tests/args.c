#include <zstdio.h>
#include <zstdlib.h>
#include <stdio.h>
int main(int argc, char** argv, char** envp)
{
    int i;
    printf("Args: %d\n", argc);
    for (i = 0; i < argc; ++i) {
        zprintf("'%s'\n", argv[i]);
    }

    printf("\nEnvp:\n");
    for (i = 0; envp[i]; ++i) {
        zprintf("'%s'\n", envp[i]);
    }
    return argc;
}
