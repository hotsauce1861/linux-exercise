#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024

using namespace std;

int main(int argc, char *argv[])
{
    int ready = 0;
    printf("start poll test");
    char buf[BUF_SIZE] = { 0 };
    int ret = 0;
    pollfd pollfds[2];
    pollfds[0].fd = open("/root/1.bin",O_RDWR);
    pollfds[0].events = POLLIN;

    pollfds[1].fd = open("/root/2.bin",O_RDWR);
    pollfds[1].events = POLLIN;

    while(1)
    {
        ready = poll(pollfds,2,1000);
        if(ready == -1){
            break;
        }
        for(int i = 0; ready > 0; i++){
            if(pollfds[i].revents & POLLIN){
                ret = read(pollfds[i].fd,(char*)buf,BUF_SIZE);
                if(ret > 0){
                    printf("\nReceive buf is %s",buf);
                }
            }
        }
        sleep(1);
    }
    return 0;
}
