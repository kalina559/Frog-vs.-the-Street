#ifndef LANE_H
#define LANE_H
#include<MainWindow.h>

class Lane: public QObject/*, public QGraphicsPixmapItem*/  //inherits from QObject so that it can connect to slots
{
    Q_OBJECT
    MainWindow * mainWindow;

public:
    Lane(MainWindow *);
    //~Lane();

public slots:
    void spawn();
};

#endif // LANE_H
