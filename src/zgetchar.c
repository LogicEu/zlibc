#include <zsys.h>

int zgetc(int fd)
{
    int c = 0;
    int err = zread(fd, &c, 1);
    return err == -1 ? err : c;
}

int zgetchar(void)
{
    return zgetc(STDIN_FILENO);
}
