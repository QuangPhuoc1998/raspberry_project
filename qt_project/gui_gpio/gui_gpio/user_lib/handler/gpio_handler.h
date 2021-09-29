#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include <QObject>
#include <QtDebug>
#include <QPoint>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

typedef enum
{
    LOW = 0,
    HIGH = 1
} gpio_level_t;

class gpio_handler_class : public QObject
{
    Q_OBJECT
public:
    explicit gpio_handler_class(QObject *parent = nullptr);
    Q_INVOKABLE void control_led();
    Q_INVOKABLE void control_init();
    Q_INVOKABLE void disable_led();
signals:

};

#endif // GPIO_HANDLER_H
