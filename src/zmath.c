#include <zmath.h>

int zipow(int x, int y)
{
    int temp;
    if (y == 0) {
        return 1;
    }

    temp = zipow(x, y / 2);
    if (y % 2) {
        return x * temp * temp;
    }
    
    return temp * temp;
}
