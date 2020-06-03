#include "Vehicle.h"
#include<iostream>
#include<stdlib.h>

Vehicle::Vehicle(GameWindow::laneDirection dir, int position, int sp):  speed(sp), direction(dir)
{
    auto vehicleType=rand() % 20;

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

    this->setData(0,GameWindow::itemType::vehicle);

    switch(direction)
    {
    case GameWindow::laneDirection::left:
        setPos(800, position - pixmap().height() / 2);
        break;
    case GameWindow::laneDirection::right:
        setPos(- pixmap().width(), position - pixmap().height() / 2);
        setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
        setRotation(180);
        break;
    }
    connect(GameWindow::timer.get(),SIGNAL(timeout()),this,SLOT(move()));
}

void Vehicle::move()
{
    if(!GameWindow::isItemVisible(GameWindow::itemType::menuPause))
    {
        switch(direction)
        {
        case GameWindow::laneDirection::left:
            setPos(x() - speed, y());
            break;
        case GameWindow::laneDirection::right:
            setPos(x() + speed, y());
            break;
        }
    }
}
