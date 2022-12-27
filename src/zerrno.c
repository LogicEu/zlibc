#include <zsys.h>
#include <zerrno.h>

extern size_t zstrlen(const char*);
extern void* zmemcpy(void*, const void*, size_t);
int zitoa(int, char*, const int);

static char* __zerrmsgs[] = {
    (char*)0,
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device / Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe"
};

static char* zstrunderr(int errnum)
{
    static const char msg[] = "Undefined error: ";
    static char buf[64];
    zmemcpy(buf, msg, sizeof(msg) - 1);
    zitoa(errnum, buf + sizeof(msg) - 1, 10);
    return buf;
}

int* __zerrno(void)
{
    static int _zerrno = 0;
    return &_zerrno;
}

char* zstrerror(int errnum)
{
    return errnum > 0 && errnum <= EPIPE ?  __zerrmsgs[errnum] : zstrunderr(errnum);
}

void zperror(const char* s)
{
    char* msg;
    int errnum = *__zerrno();
    msg = errnum > 0 && errnum <= EPIPE ?  __zerrmsgs[errnum] : zstrunderr(errnum);
    zwrite(STDERR_FILENO, s, zstrlen(s));
    zwrite(STDERR_FILENO, ": ", 2);
    zwrite(STDERR_FILENO, msg, zstrlen(msg));
    zwrite(STDERR_FILENO, "\n", 1);
}
