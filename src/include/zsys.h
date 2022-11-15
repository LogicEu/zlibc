#ifndef Z_SYSTEM_H
#define Z_SYSTEM_H

#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/mman.h>

#ifdef __APPLE__
#define SYS_BASE 0x2000000
#else
#define SYS_BASE 0x0000000
#endif

#define SYS_STDIN 0
#define SYS_STDOUT 1
#define SYS_STDERR 2

#define STDIN SYS_STDIN
#define STDOUT SYS_STDOUT
#define STDERR SYS_STDERR

__attribute__((naked)) 
long zsyscall(long op, ...);
void zsysexit(int status) __attribute__((noreturn));

int zopen(const char* fpath, int flag);
int zclose(int fd);
int zwrite(int fd, const void* buf, size_t size);
ssize_t zread(int fd, void* dst, size_t size);
int zfstat(int fd, struct stat *st);

void* zmmap(void* addr, size_t size, int prot, int flags, int fd, off_t offset);
int zmunmap(void* addr, size_t size);

#endif /* Z_SYS_H */
