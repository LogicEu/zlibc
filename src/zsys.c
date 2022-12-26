#include <zsys.h>
#include <sys/syscall.h>

long zsyscall(__attribute__((unused)) long op, ...)
{
    __asm__ volatile (
#ifdef __x86_64__
        "\tmovq %rdi, %rax\n"
        "\tmovq %rsi, %rdi\n"
        "\tmovq %rdx, %rsi\n"
        "\tmovq %rcx, %rdx\n"
        "\tmovq %r8, %r10\n"
        "\tmovq %r9, %r8\n"
        "\tmovq 8(%rsp), %r9\n"
        "\tsyscall\n"
        "\tretq\n"
#elif __arm__
        "\tmov ip, sp\n"
        "\tpush {r4, r5, r6, r7}\n"
        "\tmov r7, r0\n"
        "\tmov r0, r1\n"
        "\tmov r1, r2\n"
        "\tmov r2, r3\n"
        "\tldm ip, {r3, r4, r5, r6}\n"
        "\tsvc #0\n"
        "\tpop {r4, r5, r6, r7}\n"
        "\tbx lr\n"
#endif
    );
}

static void zsysnoret(int status) __attribute__((noreturn));
static void zsysnoret(int status)
{
    zsysexit(status);
}

void zsysexit(int status)
{
    zsyscall(SYS_exit + SYS_BASE, status);
    zsysnoret(status);
}

int zopen(const char* fpath, int flag)
{
    return zsyscall(SYS_open + SYS_BASE, fpath, flag);
}

int zclose(int fd)
{
    return zsyscall(SYS_close + SYS_BASE, fd);
}

ssize_t zwrite(int fd, const void* buf, size_t size)
{
    return zsyscall(SYS_write + SYS_BASE, fd, buf, size);
}

ssize_t zread(int fd, void* dst, size_t size)
{
    return zsyscall(SYS_read + SYS_BASE, fd, dst, size);
}

int zfstat(int fd, struct stat *st)
{
#if defined __x86_64__ && defined __APPLE__
    return zsyscall(SYS_fstat64 + SYS_BASE, fd, st);
#else 
    return zsyscall(SYS_fstatfs + SYS_BASE, fd, st);
#endif
}

off_t zlseek(int fd, off_t offset, int whence)
{
    return zsyscall(SYS_lseek + SYS_BASE, fd, offset, whence);
}

void* zmmap(void* addr, size_t size, int prot, int flags, int fd, off_t offset)
{
#if defined __x86_64__ && defined __APPLE__
    return (void*)zsyscall(SYS_mmap + SYS_BASE, addr, size, prot, flags, fd, offset);
#else 
    return (void*)zsyscall(SYS_mmap2 + SYS_BASE, addr, size, prot, flags, fd, offset);
#endif
    /* return mmap(addr, size, prot, flags, fd, offset); */
}

int zmunmap(void* addr, size_t size)
{
    return zsyscall(SYS_munmap + SYS_BASE, addr, size);
    /* return munmap(addr, size); */
}
