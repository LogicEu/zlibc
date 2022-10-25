#include <zstdio.h>
#include <zsys.h>
#include <zstring.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int zputs(const char* str)
{
    static char buf[0xffff];
    size_t len = zstrlen(str);
    zmemcpy(buf, str, len);
    buf[len++] = '\n';
    buf[len] = 0;
    zsyscall(SYS_write, STDOUT, buf, len);
    return 0;
}
