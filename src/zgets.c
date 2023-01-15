#include <zstdio.h>

char* zfgets(char* str, int size, ZFILE* stream)
{
    int i;
    char* c = str;
    --size;
    for (i = 0; i < size; ++i) {
        if (!zfread(c, sizeof(char), 1, stream) || *c == ZEOF) {
            return NULL;    
        }

        if (*c == '\n') {
            ++c;
            break;
        }

        ++c;
    }
    *c = '\0';
    return str;
}

char* zgets(char* str)
{
    char* c = str;
    while (1) {
        if (!zfread(c, sizeof(char), 1, zstdin) || *c == ZEOF) {
            return NULL;
        }

        if (*c == '\n') {
            break;
        }

        ++c;
    }
    *c = '\0';
    return str;
}

