#include <stdio.h>

int main(void)
{
    const char* str = "(a-77) : asughfewbwg jajajaj --> -10243.884664";
    char buf[0xff], c;
    int n;
    float f;

    /*zsscanf(str, "(%c-%d) : %s --> %f", &c, &n, buf, &f);
    zprintf("Char: %c\nNum: %d\nStr: %s\nFloat: %f\n", c, n, buf, f);*/
    sscanf(str, "(%c-%d) : %s --> %f", &c, &n, buf, &f);
    printf("Char: %c\nNum: %d\nStr: %s\nFloat: %f\n", c, n, buf, f);
    return 0;
}
