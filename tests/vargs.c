#include <zstdarg.h>
#include <zsys.h>

static void funcv(va_list* ap)
{
    int c;
    c = va_arg(*ap, int);
    zwrite(STDOUT_FILENO, &c, 1);
    
    c = '\n';
    zwrite(STDOUT_FILENO, &c, 1);
}

static void funcloop(int count, va_list* ap)
{
    int i;
    for (i = 0; i < count; ++i) {
        funcv(ap);
    } 
}

static void func(int count, ...)
{
    va_list ap;
    va_start(ap, count);
    funcloop(count, &ap);
    va_end(ap);
}

int main(void)
{
    func(5, 'a', 'b', 'c', 'd', 'e');
    func(5, '1', '2', '3', '4', '5');
    return 0;
}
