#include <zstdio.h>
#include <zstring.h>

int main(void)
{
    static const char* delim = ".,-?\n ";
    char buf[0xff] = "Hi there, how are you today? - I'm feeling ok...\n";
    char* tok, *str = buf;

    zprintf("Str; '%s'\nDelim: '%s'\n", buf, delim);
    while ((tok = zstrsep(&str, delim))) {
        if (*tok) {
            zprintf("'%s'\n", tok);
        }
    }
    return 0;
}
