#include <zsys.h>

long zsyscall(long op, ...)
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
        "\tmovq %rax, -8(%rbp)\n"
#elif __arm__
        "\tmov r7, r0\n"
        "\tmov r0, r1\n"
        "\tmov r1, r2\n"
        "\tmov r2, r3\n"
        "\tmov r4, r5\n"
        "\tmov r5, r6\n"
        "\tsvc #0\n"
#endif
    );
    return op;
}

int zopen(char* fpath, int flag)
{
    return zsyscall(SYS_open + SYS_OS_OFFSET, fpath, flag);
}

int zwrite(int fd, const void* buf, size_t size)
{
    return zsyscall(SYS_write + SYS_OS_OFFSET, fd, buf, size);
}

int zfstat(int fd, struct stat *st)
{
    return zsyscall(SYS_fstat64 + SYS_OS_OFFSET, fd, st);
}

void* zmmap(void* addr, size_t size, int prot, int flags, int fd, off_t offset)
{
    /*return (void*)(size_t)zsyscall(SYS_mmap + SYS_OS_OFFSET, addr, size,
     *prot, flags, fd, offset);*/
    return mmap(addr, size, prot, flags, fd, offset);
}

int zmunmap(void* addr, size_t size)
{
    /* return zsyscall(SYS_munmap + SYS_OS_OFFSET, addr, size); */
    return munmap(addr, size);
}
