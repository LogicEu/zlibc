#include <zstdio.h>
#include <zstdlib.h>
#include <zstring.h>

int main(const int argc, const char** argv)
{
    static const char* div = " /";

    int i;
    char buf[0xffff] = {0};
    for (i = 0; i < argc; ++i) {
        zstrcat(buf, argv[i]);
        zstrcat(buf, i % 2 ? "/" : " ");
    }

    char* s = zstrdup(buf);
    zprintf("'%s'\n", s);

    char* tok = zstrtok(s, div);
    
    i = 0;
    while (tok) {
        zprintf("%d.- '%s'\n", ++i, tok);
        tok = zstrtok(NULL, div);
    }

    return Z_EXIT_SUCCESS;
}
