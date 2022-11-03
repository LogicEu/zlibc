#ifndef Z_ASSERT_H
#define Z_ASSERT_H

#include <zstdlib.h>
#include <zstdio.h>

static const char* zassertmsg = "Assertion failed: %s, file %s, function %s, Line %zu.\n";

#ifndef NDEBUG
#define zassert(expr)           \
do {                            \
    if (!(expr)) {              \
        zprintf(                \
            zassertmsg,         \
            #expr,              \
            __FILE__,           \
            __FUNCTION__,       \
            __LINE__            \
        );                      \
        zexit(Z_EXIT_FAILURE);  \
    }                           \
} while (0)
#else
#define zassert(expr) ((void)0)
#endif /* NDEBUG */
#endif /* Z_ASSERT */
