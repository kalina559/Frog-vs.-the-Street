#ifndef VEHICLE_H
#define VEHICLE_H
#include<QGraphicsPixmapItem>
#include<MainWindow.h>
#include<QObject>

class Vehicle: public QObject, public QGraphicsPixmapItem     //inherits from QObject so that it can connect to slots
{
    Q_OBJECT
    int velocity;
    MainWindow::laneDirection direction;
    //Lane * lane;
    int position;
    MainWindow * mainWindow;
public:
    Vehicle(MainWindow *, MainWindow::laneDirection, int, int);
    ~Vehicle();
    int getVehicleSpeed()
    {
        return velocity;
    }
public slots:
    void move();
};

#endif // VEHICLE_H
