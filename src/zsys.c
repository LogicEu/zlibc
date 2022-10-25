#include <zsys.h>

int zsyscall(int op, ...)
{
    __asm__(
#ifdef __x86_64__
        "\tmovq %rdi, %rax\n"
        "\tmovq %rsi, %rdi\n"
        "\tmovq %rdx, %rsi\n"
        "\tmovq %rcx, %rdx\n"
        "\tmovq %r8, %r10\n"
        "\tmovq %r9, %r8\n"
        "\tmovq 8(%rsp), %r9\n"
        "\tsyscall\n"
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