#include <zstdio.h>

int main(int argc, char** argv, char** envp)
{
    int i;
    zprintf("Args: %d\n", argc);
    for (i = 0; i < argc; ++i)
        zprintf("'%s'\n", argv[i]);
    zprintf("\nEnvp:\n");
    for (i = 0; envp[i]; ++i)
        zprintf("'%s'\n", envp[i]);
    return argc;
}
