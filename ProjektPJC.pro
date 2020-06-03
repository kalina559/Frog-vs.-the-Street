QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjektPJC

TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"
CONFIG += c++14

SOURCES += \
        GameWindow.cpp \
        Lane.cpp \
        Player.cpp \
        Score.cpp \
        Vehicle.cpp \
        main.cpp

RESOURCES += \
    resources.qrc

HEADERS += \
    GameWindow.h \
    Lane.h \
    Player.h \
    Score.h \
    Vehicle.h
