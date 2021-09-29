#include "gpio_handler.h"

#define FILE_NAME "/dev/etx_device"
int fd;

gpio_handler_class::gpio_handler_class(QObject *parent) : QObject(parent)
{
    fd = open(FILE_NAME, O_RDWR);
    if (fd < 0)
    {
        qDebug() << "ERROR: can't open file\n";
    }
    else
    {
        qDebug() << "Open file success\n";
    }
}
void gpio_handler_class::control_init()
{

}
void gpio_handler_class::control_led()
{
    static gpio_level_t led_status = LOW;
    if (led_status == LOW)
    {
        qDebug() << "Led on";
        write(fd,"1", 1);
        led_status = HIGH;
    }
    else
    {
        qDebug() << "Led off";
        write(fd,"0", 1);
        led_status = LOW;
    }
}
void gpio_handler_class::disable_led()
{
    write(fd,"0", 1);
    close(fd);
}

