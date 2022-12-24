#include <zsys.h>
#include <zstdlib.h>

int main(int argc, char** argv)
{
    int fd;
    char* data;
    struct stat st;
    size_t len;

    if (argc < 2) {
        static const char err[] = "Missing input file.\n";
        zwrite(STDOUT_FILENO, err, sizeof(err) - 1);
        return Z_EXIT_FAILURE;
    }

    fd = zopen(argv[1], O_RDONLY);
    if (fd < 0) {
        static const char err[] = "Could not open file '", close[] = "'\n";
        for (len = 0; argv[1][len]; ++len);
        zwrite(STDOUT_FILENO, err, sizeof(err) - 1);
        zwrite(STDOUT_FILENO, argv[1], len);
        zwrite(STDOUT_FILENO, close, sizeof(close) - 1);
        return Z_EXIT_FAILURE;
    }

    zfstat(fd, &st);
    len = (size_t)st.st_size;
    data = zmalloc(len + 1);
    zread(fd, data, len);
    data[len] = 0;
    zwrite(STDOUT_FILENO, data, len);
    zfree(data);
    return Z_EXIT_SUCCESS;
}
