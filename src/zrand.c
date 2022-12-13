#include <zstdlib.h>

static unsigned int r[344] = {0};
static int n = 0;

void zsrand(unsigned int seed)
{
    int i;
    r[0] = seed;
    
	for (i = 1; i < 31; i++) {
        r[i] = (unsigned int)((16807 * (unsigned long)r[i - 1]) % 2147483647);
    }
    
    for (; i < 34; i++) {
        r[i] = r[i - 31];
    }
    
    for (; i < 344; i++) {
        r[i] = r[i - 31] + r[i - 3];
    }

    n = 0;
}

int zrand(void)
{
    unsigned int x = r[n % 344] = r[(n + 313) % 344] + r[(n + 341) % 344];
    n = (n + 1) % 344;
    return (int)(x >> 1);
}
