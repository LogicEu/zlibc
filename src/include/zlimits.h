#ifndef Z_LIMITS_H
#define Z_LIMITS_H

#include <zstddef.h>

#define Z_SIZE_MAX ((size_t)(-1))
#define Z_ULONG_MAX ((unsigned long)(-1))
#define Z_UINT_MAX ((unsigned int)(-1))
#define Z_USHORT_MAX ((unsigned short)(-1))
#define Z_UCHAR_MAX ((unsigned char)(-1))

#define Z_LONG_MAX 0x7FFFFFFFFFFFFFFFL
#define Z_LONG_MIN 0x8000000000000000L
#define Z_INT_MAX 0x7FFFFFFF
#define Z_INT_MIN 0x80000000
#define Z_SHORT_MAX 0x7FFF
#define Z_SHORT_MIN 0x8000
#define Z_CHAR_MAX 0x7F
#define Z_CHAR_MIN 0x80

#endif /* Z_LIMITS_H */

