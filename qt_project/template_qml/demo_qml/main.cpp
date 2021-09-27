#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <gpio_handler.h>
#include <system_handler.h>
#include <bsp_gpio.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv); /*-*/

    QScopedPointer<gpio_handler_class> gpio_handler_pointer(new gpio_handler_class); /*-*/
    QScopedPointer<system_handler_class> system_handler_pointer(new system_handler_class); /*-*/


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    engine.rootContext()->setContextProperty("gpio_handler",gpio_handler_pointer.data()); /*-*/
    engine.rootContext()->setContextProperty("system_handler",system_handler_pointer.data()); /*-*/

    /*--- bsp init ---*/
    bsp_gpio_init();
    bsp_gpio_set_output(LED);

    return app.exec();
}
