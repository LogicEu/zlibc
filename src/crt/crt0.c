extern int main();
extern void zexit(int status);
extern int zprintf(const char* fmt, ...);

void start(int argc, char** argv, char** envp)
{
#ifdef __arm__
    int i;
    
    (void)argc;
    (void)argv;

    for (i = 0; envp[i]; ++i);
    zexit(main(i, envp, envp + i + 1));

#else

    zexit(main(argc, argv, envp));

#endif
}
