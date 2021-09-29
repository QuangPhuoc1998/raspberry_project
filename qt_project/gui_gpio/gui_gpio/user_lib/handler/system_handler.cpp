#include <system_handler.h>
#include <QProcess>

QProcess process;

system_handler_class::system_handler_class(QObject *parent) : QObject(parent)
{

}

void system_handler_class::system_gui_off()
{
    qDebug() << "Power off";
    process.startDetached("shutdown -h now");
}


