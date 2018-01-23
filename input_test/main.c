#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    printf("\ninput event detect");
    int i_fd = 0;
    struct input_event input_t;
    i_fd = open("/dev/input/event1",O_RDONLY);

    if(i_fd <= 0){
        printf("\nopen input device failed");
        return -1;
    }
    while(1)
    {
        if(read(i_fd, &input_t, sizeof(input_t))){
            if( input_t.type == EV_KEY){
                if(input_t.value == 0 || input_t.value == 1){
                    printf("\n detect key %d %s",input_t.code,input_t.value ? "released":"pressed");
                }
            }
        }
    }
    close(i_fd);
    return 0;
}
