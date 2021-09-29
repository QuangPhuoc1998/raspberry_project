#include "bsp_gpio.h"

unsigned int __iomem * gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

int8_t bsp_gpio_init(void)
{
    if ((gpio = ioremap(GPIO_BASE, 0xf0)) == NULL) {
        printk(KERN_INFO "io remap failed\n");
        return -1;
    }
    return 0;
}
void bps_gpio_deinit(void)
{
    iounmap(gpio);
}
void bsp_gpio_set_input(uint8_t pin)
{
    INP_GPIO(pin);
}
void bsp_gpio_set_output(uint8_t pin)
{
    INP_GPIO(pin);
    OUT_GPIO(pin);
}
void bsp_gpio_write(uint8_t pin, gpio_level_t level)
{
    (level == HIGH) ? (GPIO_SET = 1<<pin):(GPIO_CLR = 1<<pin);
}
uint8_t bsp_gpio_read(uint8_t pin)
{
    return GET_GPIO(pin);
}