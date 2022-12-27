#include <zsys.h>

int main(const int argc, const char** argv)
{
    int fd, c;
    size_t size, i;
    struct stat st;
    const char* fpath;

    if (argc < 2) {
        static const char msg[] = "Missing input file.\n";
        zwrite(STDERR_FILENO, msg, sizeof(msg) - 1);
        return 1;
    }
 
    fpath = argv[1];
    fd = zopen(fpath, O_RDONLY);
    if (fd < 0) {
        static const char msg[] = "Could not open file ", nl = '\n';
        for (i = 0; fpath[i]; ++i);
        zwrite(STDERR_FILENO, msg, sizeof(msg) - 1);
        zwrite(STDERR_FILENO, fpath, i);
        zwrite(STDERR_FILENO, &nl, 1); 
        return -1;
    }
   
    zfstat(fd, &st);
    size = (size_t)st.st_size;
    for (i = 0; i < size; ++i) {
        zread(fd, &c, 1);
        zwrite(STDOUT_FILENO, &c, 1); 
    }

    zclose(fd);
    return 0;
}
