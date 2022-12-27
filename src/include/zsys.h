#ifndef Z_SYSTEM_H
#define Z_SYSTEM_H

#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

#ifdef __APPLE__
#define SYS_BASE 0x2000000
#else
#define SYS_BASE 0x0000000
#endif

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

__attribute__((naked)) 
long zsyscall(long op, ...);
void zsysexit(int status) __attribute__((noreturn));

__attribute__((naked)) 
int zopen(const char* fpath, int flag, ...);
int zclose(int fd);
ssize_t zwrite(int fd, const void* buf, size_t size);
ssize_t zread(int fd, void* dst, size_t size);
int zfstat(int fd, struct stat *st);
off_t zlseek(int fd, off_t offset, int whence);

void* zmmap(void* addr, size_t size, int prot, int flags, int fd, off_t offset);
int zmunmap(void* addr, size_t size);

#endif /* Z_SYS_H */
