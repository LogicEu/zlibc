#ifndef Z_SYSTEM_H
#define Z_SYSTEM_H

#define SYS_exit  0x2000001
#define SYS_fork  0x2000002
#define SYS_read  0x2000003
#define SYS_write 0x2000004
#define SYS_open  0x2000005
#define SYS_close 0x2000006
#define SYS_creat 0x2000008
#define SYS_lseek 0x2000019

__attribute__((optimize("O0"))) 
int zsyscall(int op, ...);

#endif /* Z_SYS_H */
