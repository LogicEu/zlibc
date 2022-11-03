#ifndef Z_STDIO_H
#define Z_STDIO_H

#define BUFSIZ 1024

int zsnprintf(char* buf, size_t size, const char* fmt, ...);
int zsprintf(char* buf, const char* fmt, ...);
int zdprintf(int fd, const char* fmt, ...);
int zprintf(const char* str, ...);

#endif /* Z_STDIO_H */
