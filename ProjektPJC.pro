QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjektPJC

TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14

SOURCES += \
        Frog.cpp \
        Interface.cpp \
        MainWindow.cpp \
        main.cpp

RESOURCES += \
    resources.qrc

HEADERS += \
    Frog.h \
    Interface.h \
    MainWindow.h
