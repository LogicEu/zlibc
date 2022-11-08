#ifndef Z_SYSTEM_H
#define Z_SYSTEM_H

#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#ifdef __APPLE__
#define SYS_OS_OFFSET 0x2000000
#else
#define SYS_OS_OFFSET 0x0000000
#endif

#define SYS_STDIN 0
#define SYS_STDOUT 1
#define SYS_STDERR 2

#if defined (__clang__)
    #define optnone __attribute__((optnone))
#elif defined (__GNUC__)
    #define optnone __attribute__((optimize("O0")))
#else
    #define optnone 
#endif

optnone
int zsyscall(int op, ...);

#endif /* Z_SYS_H */
