#include "Vehicle.h"
#include<QTimer>
#include<iostream>

Vehicle::Vehicle(Lane * lane): lane(lane)
{
    std::cout<<"vehicle constr"<<std::endl;
    setPixmap(QPixmap(":/images/hotrod.png"));

    velocity = 10;   // do zmiany

    timer = new QTimer;   //deleted in ~Vehicle()
    setPos(800, 50);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

Vehicle::~Vehicle()
{
    std::cout<<"usunieto furke"<<std::endl;
    delete(this->timer);
}

void Vehicle::move()
{
    std::cout<<"pos:"<<x()<<std::endl;
    setPos(x() - velocity, y());

    if(x() < -(pixmap().width()+ 10))
    {
        delete(this);
    }
}
