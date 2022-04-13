#include "main.h"

#define FILE_NAME "/dev/gy30_device"
#define DATA_LEN 2

uint8_t g_aubI2CReadData[DATA_LEN] = {0};
uint16_t g_uwGy30Data = 0;

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
        read(fd, g_aubI2CReadData ,DATA_LEN);
		g_uwGy30Data = (g_aubI2CReadData[0] << 8 ) + g_aubI2CReadData[1] / 1.2 ;
		printf("Data =  %d\n", g_uwGy30Data);
		sleep(1);
    }
    close(fd);
    return 0;
}