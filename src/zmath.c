#include <zmath.h>

int zpow(int x, int y)
{
    int temp;
    if (y == 0) {
        return 1;
    }

    temp = zpow(x, y / 2);
    if (y % 2) {
        return x * temp * temp;
    }
    
    return temp * temp;
}