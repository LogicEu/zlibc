#include <zerrno.h>
#include <zstdio.h>
#include <zstring.h>

int main(int argc, char** argv)
{
    char* s;
    (void)argc;
    zperror(argv[0]);
    zerrno = 78352;
    zperror(argv[0]);
    zerrno = EPERM;
    s = zstrerror(zerrno);
    zprintf("%s: %s: %s\n", argv[0], s, argv[1]);
    zerrno = 0;
    s = zstrerror(zerrno);
    zprintf("%s: %s: %s\n", argv[0], s, argv[1]);
    return 0;
}
