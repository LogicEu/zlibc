#include <zstdio.h>
#include <zstdlib.h>
#include <zstring.h>
#include <zsys.h>

static void zinout(const char* str)
{
    size_t linecap = 0;
    char* line = NULL;
    ssize_t linelen;
   
    while (1) {
        zprintf("%s", str);
        linelen = zgetline(&line, &linecap, SYS_STDIN);
        line[--linelen] = 0;
        if (!zstrcmp(line, "exit")) {
            break;
        }
        zprintf("%lu.- '%s'\n", linelen, line);
    }

    zfree(line);
}

int main(void)
{
    zinout("Write something to stdin: ");
    return Z_EXIT_FAILURE;
}
