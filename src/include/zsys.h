#ifndef Z_SYSTEM_H
#define Z_SYSTEM_H

#ifdef __APPLE__
    #define SYS_exit  0x2000001
    #define SYS_fork  0x2000002
    #define SYS_read  0x2000003
    #define SYS_write 0x2000004
    #define SYS_open  0x2000005
    #define SYS_close 0x2000006
    #define SYS_creat 0x2000008
    #define SYS_lseek 0x2000019
#else
    #define SYS_exit  0x0000001
    #define SYS_fork  0x0000002
    #define SYS_read  0x0000003
    #define SYS_write 0x0000004
    #define SYS_open  0x0000005
    #define SYS_close 0x0000006
    #define SYS_creat 0x0000008
    #define SYS_lseek 0x0000019
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
