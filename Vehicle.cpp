#include "Vehicle.h"
#include<iostream>
#include<stdlib.h>

Vehicle::Vehicle(MainWindow * main, int position, int vel): mainWindow(main)   //when there's no car on the lane yet
{
    std::cout<<"vehicle constr"<<std::endl;
    auto vehicleType=rand()%20;

    //rysowanie pojazdu (w zależności od pasa)
    if(vehicleType < 7)
        setPixmap(QPixmap(":/images/hotrod.png"));
    else if(vehicleType < 11)
        setPixmap(QPixmap(":/images/taxi.png"));
    else if(vehicleType < 13)
        setPixmap(QPixmap(":/images/police1.png"));
    else if(vehicleType < 15)
        setPixmap(QPixmap(":/images/police.png"));
    else if(vehicleType < 17)
        setPixmap(QPixmap(":/images/truck.png"));
    else if(vehicleType < 20)
        setPixmap(QPixmap(":/images/bike.png"));

    this->setData(0,MainWindow::itemType::vehicle);

    velocity = vel;

    setPos(800, position - pixmap().height() / 2);
    connect(MainWindow::timer.get(),SIGNAL(timeout()),this,SLOT(move()));
}

Vehicle::~Vehicle()
{
    std::cout<<"usunieto furke"<<std::endl;

}

void Vehicle::move()
{
    if(!mainWindow->isItemVisible(MainWindow::itemType::menuPause))
    {
        setPos(x() - velocity, y());

//        if(x() < -(pixmap().width()))
//        {
//            delete(this);
//        }
    }
}
