#include "gpio_handler.h"
#include "bsp_gpio.h"

gpio_handler_class::gpio_handler_class(QObject *parent) : QObject(parent)
{

}

void gpio_handler_class::control_led()
{
    static gpio_level_t led_status = LOW;
    if (led_status == LOW)
    {
        qDebug() << "Led on\n";
        bsp_gpio_write(LED, HIGH);
        led_status = HIGH;
    }
    else
    {
        qDebug() << "Led off\n";
        bsp_gpio_write(LED, LOW);
        led_status = LOW;
    }
}
void gpio_handler_class::disable_led()
{
    bsp_gpio_write(LED, LOW);
}

