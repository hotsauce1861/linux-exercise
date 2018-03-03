#define __USE_POSIX199309
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

    struct sigaction    act, oldact;

    int n = 0;
    void (*oldHandle)(int sig);
    oldHandle = handle;
    //act.__sigaction_handler = oldHandle;
    act.sa_handler = handle;
    act.sa_flags = SA_SIGINFO;
    if(sigaction(SIGINT,&act,&oldact) == SIG_ERR)
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
