#include <zsys.h>
#include <zstdlib.h>

#define Z_ATEXIT_FUNC_MAX 32

static void (*zexit_funcs[Z_ATEXIT_FUNC_MAX])(void) = {NULL};
static int zexit_funccount = 0;

int zatexit(void (*function)(void))
{
    static const char errmsg[] = "zatexit only supports 32 functions to be registered.\n";
    if (zexit_funccount == Z_ATEXIT_FUNC_MAX) {
        zwrite(STDERR, errmsg, sizeof(errmsg));
        return -1;
    }
    
    zexit_funcs[zexit_funccount++] = function;
    return 0;
}

void zexit(int status)
{
    while (--zexit_funccount >= 0) {
        zexit_funcs[zexit_funccount]();
    }
    zsysexit(status);
}

void zabort(void)
{
    static const char errmsg[] = "zabort!\n";
    zwrite(STDERR, errmsg, sizeof(errmsg));
    zsysexit(Z_EXIT_FAILURE);
}
