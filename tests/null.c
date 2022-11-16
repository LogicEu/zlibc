#include <zstdio.h>
#include <zstdlib.h>
#include <zstring.h>
int main(void)
{
    const char* s = "";
    const char* n = NULL;
    zprintf("'%s', '%s'\n", s, n);
    return Z_EXIT_SUCCESS;
}
