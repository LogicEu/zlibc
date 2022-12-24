#include <zstdio.h>
#include <zstdlib.h>

int main(void)
{
    size_t cap = 0;
    char* line = NULL;
    ssize_t len;

    while ((len = zgetdelim(&line, &cap, ' ', STDIN_FILENO)) != -1) {
        line[len - 1] = 0;
        zprintf("%ld.- '%s'\n", len, line);
    }

    return Z_EXIT_SUCCESS;
}
