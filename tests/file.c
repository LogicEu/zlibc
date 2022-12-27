#include <zstdio.h>
#include <zstdlib.h>

static char* zfileread(const char* path, size_t* size)
{
    char* data;
    ZFILE* file = zfopen(path, "rb");
    if (!file) {
        return NULL;
    }
    
    zfseek(file, 0, Z_SEEK_END);
    *size = (size_t)zftell(file);
    zfseek(file, 0, Z_SEEK_SET);
    data = zmalloc(*size);
    zfread(data, *size, 1, file);
    zfclose(file);
    return data;
}

static void zfilewrite(const char* path, const void* data, size_t size)
{
    ZFILE* file = zfopen(path, "wb");
    if (!file) {
        zprintf("Could not write file '%s'\n", path);
        return;
    }
    zfwrite(data, size, 1, file);
    zfclose(file);
}

static void zfileappend(const char* path, const void* data, size_t size)
{
    ZFILE* file = zfopen(path, "ab");
    if (!file) {
        zprintf("Could not write file '%s'\n", path);
        return;
    }
    zfwrite(data, size, 1, file);
    zprintf("Size: %ld\n", zftell(file));
    zfclose(file);
}

int main(const int argc, const char** argv)
{
    size_t len;
    char* data;
    if (argc < 2) {
        zprintf("Missing input file.\n");
        return Z_EXIT_FAILURE; 
    }

    data = zfileread(argv[1], &len);
    if (!data) {
        zprintf("Could not open file '%s'\n", argv[1]);
        return Z_EXIT_FAILURE;
    }

    zprintf("Size: %zu\n'%s'\n", len, data);
    zfilewrite("tmp.txt", data, len);
    zfileappend("tmp.txt", data, len);
    
    zfree(data);
    return Z_EXIT_SUCCESS;
}
