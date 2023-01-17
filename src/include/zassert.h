#ifndef Z_ASSERT_H
#define Z_ASSERT_H

#include <zstdlib.h>
#include <zstdio.h>

#ifndef NDEBUG

__attribute__((unused))
static const char* zassertmsg = "Assertion failed: %s, file %s,"
#ifdef __STDC_VERSION__
                                "function %s,"
#endif
                                "line %zu.\n";

#ifdef __STDC_VERSION__
#define Z_ASSERT_ARGS __FILE__, __func__, __LINE__
#else
#define Z_ASSERT_ARGS __FILE__, __LINE__
#endif

#define zassert(expr)                               \
do {                                                \
    if (!(expr)) {                                  \
        zprintf(zassertmsg, #expr, Z_ASSERT_ARGS);  \
        zabort();                                   \
    }                                               \
} while (0)

#else /* NDEBUG */
#define zassert(expr) ((void)0)
#endif /* NDEBUG */
#endif /* Z_ASSERT */

