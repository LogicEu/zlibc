extern int main();
extern void zexit(int);

void start(int argc, char** argv, char** envp)
{
    int ret;
#ifdef __arm__
    argc = (int)argv;
    argv = envp;
    envp = argv + argc + 1;
#endif
    ret = main(argc, argv, envp);
    zexit(ret);
}

