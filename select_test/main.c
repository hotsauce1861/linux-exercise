#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <linux/input.h>

#define DEV_NUM     4

#define DEV_1       "/dev/input/event1"
#define DEV_2       "/dev/input/event2"
#define DEV_3       "/dev/input/event3"
#define DEV_4       "/dev/input/event4"

int main(int argc, char *argv[])
{
    int fd_dev1,fd_dev2,fd_dev3,fd_dev4,fd_max;
    int i;
    int fd_group[DEV_NUM];
    struct input_event input_t;
    fd_set rfds;
    struct timeval tv;
    int retval;
    system("cat /proc/bus/input/devices > devices.info");
    /* Watch stdin (fd 0) to see when it has input. */

    fd_dev1 = open(DEV_1, O_RDWR);
    if(fd_dev1 < 0)
    {
        printf("fd_dev1 opened failed");
        return;
    }

    fd_dev2 = open(DEV_2, O_RDWR);
    if(fd_dev2 < 0)
    {
        printf("fd_dev2 opened failed");
        return;
    }

    fd_dev3 = open(DEV_3, O_RDWR);
    if(fd_dev3 < 0)
    {
        printf("fd_dev3 opened failed");
        return;
    }

    fd_dev4 = open(DEV_4, O_RDWR);
    if(fd_dev4 < 0)
    {
        printf("fd_dev4 opened failed");
        return;
    }

    FD_ZERO(&rfds);
    FD_SET(fd_dev1, &rfds);
    FD_SET(fd_dev2, &rfds);
    FD_SET(fd_dev3, &rfds);
    FD_SET(fd_dev4, &rfds);

    if(fd_max<fd_dev1)fd_max = fd_dev1;
    if(fd_max<fd_dev2)fd_max = fd_dev2;
    if(fd_max<fd_dev3)fd_max = fd_dev3;
    if(fd_max<fd_dev4)fd_max = fd_dev4;

    /* Wait up to five seconds. */
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    fd_group[0] = fd_dev1;
    fd_group[1] = fd_dev2;
    fd_group[2] = fd_dev3;
    fd_group[3] = fd_dev4;

    while(1)
    {

        retval = select(fd_max + 1, &rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */
        if (retval == -1)
        {
            perror("select()");
        }
        else if (retval)
        {
            /* FD_ISSET(0, &rfds) will be true. */
            for(i = 0; i<DEV_NUM; i++)
            {
                if(FD_ISSET(fd_group[i],&rfds))
                {
                    read(fd_group[i], &input_t, sizeof(input_t));
                    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
                    printf("fd index %d\n",fd_group[i]);
                    printf("input_t.code %d\n",input_t.code);
                    printf("input_t.code %d\n",input_t.time);
                    printf("input_t.value %d\n",input_t.value);
                }
            }
            printf("Data is available now.\n");
        }
        else
        {
            printf("No data within five seconds.\n");
        }
        usleep(1000);
    }
    exit(EXIT_SUCCESS);

    return 0;
}
