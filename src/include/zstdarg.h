#ifndef Z_STDARG_H
#define Z_STDARG_H

#include <zstddef.h>

typedef __builtin_va_list va_list;
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_copy(ap, type) __builtin_va_copy(ap, type)

int zvsnprintf(char* buf, size_t size, const char* fmt, va_list ap);
int zvsprintf(char* buf, const char* fmt, va_list ap);
int zvdprintf(int fd, const char* fmt, va_list ap);
int zvprintf(const char* str, va_list ap);

int zvsscanf(const char* str, const char* fmt, va_list ap);

#endif /* Z_STDARG_H */

