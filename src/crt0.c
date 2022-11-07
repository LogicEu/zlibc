extern int main();
extern void zexit(int status);

void start(int argc, char** argv, char** envp)
{
    int ret = main(argc, argv, envp);
    zexit(ret);
}
