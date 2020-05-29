#ifndef VEHICLE_H
#define VEHICLE_H
#include<QGraphicsPixmapItem>
#include<Lane.h>
#include<QObject>

class Vehicle: public QObject, public QGraphicsPixmapItem     //inherits from QObject so that it can connect to slots
{
    Q_OBJECT
    int velocity;
    QTimer * timer;
    Lane * lane;
public:
    Vehicle(Lane *);
    ~Vehicle();
public slots:
    void move();
};

#endif // VEHICLE_H
