#include "main.h"

#define FILE_NAME "/dev/Dial_device"
#define DATA_LEN 2

uint8_t g_aubDialValue[DATA_LEN] = {0};

int main (int argc, char *argv[])
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
        read(fd, g_aubDialValue ,DATA_LEN);
		printf("Dial direct: %d\n", g_aubDialValue[0]);
        printf("Dial value: %d\n\n", g_aubDialValue[1]);
		sleep(1);
    }
    close(fd);
    return 0;
}