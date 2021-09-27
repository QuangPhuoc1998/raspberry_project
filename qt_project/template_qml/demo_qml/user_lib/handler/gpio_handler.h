#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include <QObject>
#include <QtDebug>
#include <QPoint>

#define LED 17

class gpio_handler_class : public QObject
{
    Q_OBJECT
public:
    explicit gpio_handler_class(QObject *parent = nullptr);
    Q_INVOKABLE void control_led();
    Q_INVOKABLE void disable_led();
signals:

};

#endif // GPIO_HANDLER_H
