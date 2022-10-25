#include <zsys.h>

int zsyscall(int op, ...)
{
    __asm__(
        "\tmovq %rdi, %rax\n"
        "\tmovq %rsi, %rdi\n"
        "\tmovq %rdx, %rsi\n"
        "\tmovq %rcx, %rdx\n"
        "\tmovq %r8, %r10\n"
        "\tmovq %r9, %r8\n"
        "\tmovq 8(%rsp), %r9\n"
        "\tsyscall\n"
    );
    return op;
}