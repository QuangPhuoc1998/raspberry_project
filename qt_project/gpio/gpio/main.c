#include "bsp.h"
#include "bsp_gpio.h"

#define LED 17

int main()
{
    bsp_gpio_init();
    bsp_gpio_set_output(LED);
    while(1)
    {
        bsp_gpio_write(LED, HIGH);
        sleep(1);
        printf("Led %d on using lib\n", LED);
        bsp_gpio_write(LED, LOW);
        sleep(1);
        printf("Led %d off using lib\n", LED);
    }
    return 0;

} // main

