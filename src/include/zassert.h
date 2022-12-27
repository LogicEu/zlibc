#ifndef Z_ASSERT_H
#define Z_ASSERT_H

#include <zstdlib.h>
#include <zstdio.h>

#ifndef NDEBUG

__attribute__((unused))
static const char* zassertmsg = "Assertion failed: %s, file %s, function %s, Line %zu.\n";

#define zassert(expr)           \
do {                            \
    if (!(expr)) {              \
        zprintf(                \
            zassertmsg,         \
            #expr,              \
            __FILE__,           \
            __func__,           \
            __LINE__            \
        );                      \
        zabort();               \
    }                           \
} while (0)
#else
#define zassert(expr) ((void)0)
#endif /* NDEBUG */

#endif /* Z_ASSERT */
