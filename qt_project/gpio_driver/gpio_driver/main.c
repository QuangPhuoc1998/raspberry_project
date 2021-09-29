#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define FILE_NAME "/dev/etx_device"

int main()
{
    int fd = open(FILE_NAME, O_RDWR);
    if (fd < 0)
    {
        printf("ERROR: can't open file\n");
        return -1;
    }
    printf("Open file success\n");
    while(1)
    {
        printf("On led\n");
        write(fd,"1", 1);
        sleep(1);
        printf("Off led\n");
        write(fd,"0", 1);
        sleep(1);
    }
    write(fd,"0", 1);
    close(fd);
    return 0;
}
