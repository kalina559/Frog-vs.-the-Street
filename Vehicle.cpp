#include "Vehicle.h"
#include<iostream>
#include<stdlib.h>

Vehicle::Vehicle(MainWindow * main, MainWindow::laneDirection dir, int position, int vel):  velocity(vel), direction(dir), mainWindow(main)
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

    this->setData(0,MainWindow::itemType::vehicle);

    switch(direction)
    {
    case MainWindow::laneDirection::left:
        setPos(800, position - pixmap().height() / 2);
        break;
    case MainWindow::laneDirection::right:
        setPos(- pixmap().width(), position - pixmap().height() / 2);
        setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
        setRotation(180);
        break;
    }
    connect(MainWindow::timer.get(),SIGNAL(timeout()),this,SLOT(move()));
}

void Vehicle::move()
{
    if(!mainWindow->isItemVisible(MainWindow::itemType::menuPause))
    {
        switch(direction)
        {
        case MainWindow::laneDirection::left:
            setPos(x() - velocity, y());
            break;
        case MainWindow::laneDirection::right:
            setPos(x() + velocity, y());
            break;
        }
    }
}
