#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "bsp.h"

typedef enum
{
    LOW  = 0,
    HIGH = 1
} gpio_level_t;

void bsp_gpio_init(void);
void bsp_gpio_set_input(uint8_t pin);
void bsp_gpio_set_output(uint8_t pin);
void bsp_gpio_write(uint8_t pin, gpio_level_t level);
void bsp_gpio_read(uint8_t pin);

#endif // BSP_GPIO_H
