#include <zstdio.h>
#include <zstring.h>

int main(void)
{
    const char* str = "Hello World!";
    const char* charset = "HeloWd?";
    size_t index = zstrspn(str, charset);
    size_t index2 = zstrcspn(str, charset);
    zprintf(
        "Str: '%s'\nCharset: '%s'\nIndex: %zu\nIndex 2: %zu\n",
        str,
        charset,
        index,
        index2
    );
    return 0;
}
