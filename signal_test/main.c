#include <stdio.h>
#include <signal.h>

static void handle(int sig)
{
    /*
     * signal function
    */
    printf("signal function\n");
}

int main(int argc, char *argv[])
{
    int n = 0;
    void (*oldHandle)(int sig);
    oldHandle = handle;
    if(signal(SIGINT,oldHandle) == SIG_ERR )
    {
        printf("sig error\n");
    }

    for(;;n++)
    {
        printf("current number is %d \n", n);
        sleep(3);
    }

    return 0;
}
