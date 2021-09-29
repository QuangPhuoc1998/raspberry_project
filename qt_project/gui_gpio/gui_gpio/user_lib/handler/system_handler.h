#ifndef SYSTEM_HANDLER_H
#define SYSTEM_HANDLER_H

#include <QObject>
#include <QtDebug>
#include <QPoint>

class system_handler_class : public QObject
{
    Q_OBJECT
public:
    explicit system_handler_class(QObject *parent = nullptr);
    Q_INVOKABLE void system_gui_off();
signals:

};

#endif // SYSTEM_HANDLER_H
