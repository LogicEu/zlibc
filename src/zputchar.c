#include <zsys.h>

int zputc(int c, int fd)
{
    char ch = (char)c;
    int err = zwrite(fd, &ch, 1);
    return err == -1 ? err : c;
}

int zputchar(int c)
{
    return zputc(c, STDOUT_FILENO);
}
