TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        user_lib/bsp/bsp_gpio.c

HEADERS += \
    user_lib/bsp/bsp.h \
    user_lib/bsp/bsp_gpio.h

INCLUDEPATH += user_lib/bsp/
