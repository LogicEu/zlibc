#ifndef Z_MATH_H
#define Z_MATH_H

#define HUGE_VAL 1e500
#define HUGE_VALF 1e50f
#define HUGE_VALL 1e5000L
#define NAN __nan()
#define INFINITY HUGE_VALF
#define M_PI   3.14159265358979323846264338327950288

#define isnan(f) ((f) == NAN)
#define isinf(f) (((f) == INF) || ((f) == -INF))
#define isfinite(f) (!isnan(f) && !isinf(f))
#define signbit(f) ((*(((char*)&f) + sizeof(f) - 1) >> 7) & 1)

int zipow(int x, int y);

#endif /* Z_MATH_H */
