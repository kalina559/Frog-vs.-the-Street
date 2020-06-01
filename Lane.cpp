#include "Lane.h"
#include<iostream>
#include<Vehicle.h>
#include<math.h>
#include <stdlib.h>
#include<time.h>

Lane::Lane(MainWindow * game, int lane): mainWindow(game), lanePosition(lane)
{
    minSpeed = 5;
    deleteTimer = std::make_unique<QTimer>(new QTimer());
    connect(deleteTimer.get(),SIGNAL(timeout()), this, SLOT(deleteOutOfScene()));
    deleteTimer.get()->start(50);
}

Lane::~Lane()
{
    std::cout<<"usunieto lane"<<std::endl;
}
void Lane::spawn()
{
    if(!mainWindow->isItemVisible(MainWindow::itemType::menuPause))
    {

        Vehicle *  vehicle = new Vehicle(mainWindow, lanePosition, randomSpeed());  // deleted in Vehicle::move(), when it goes out of scene
        currentVehicles.push_back(vehicle);
        mainWindow->addToScene(vehicle);
    }
}
void Lane::deleteOutOfScene()
{
    if(currentVehicles.size() > 0)
    {
        if(currentVehicles.front()->pos().x() < - currentVehicles.front()->pixmap().width())
        {
            Vehicle * outOfScene = currentVehicles.front();
            currentVehicles.erase(currentVehicles.begin() + 0);
            delete(outOfScene);

            std::cout<<"dlugosc wektora fur: "<< currentVehicles.size()<<std::endl;
        }
    }
}

int Lane::randomSpeed()
{

    double maxSpeed;
    if(currentVehicles.size() == 0)
    {
        maxSpeed = rand() % 5 + 10;
        std::cout<<"pusto bylo: "<< maxSpeed << std::endl;
        return int(maxSpeed);
    }
    else
    {
        maxSpeed = floor((800 * currentVehicles.back()->getVehicleSpeed())/(currentVehicles.back()->pos().x()
                                                                      + currentVehicles.back()->pixmap().width()));
        std::cout<<"max speed: "<< maxSpeed << std::endl;
    }
        return rand() % (int(maxSpeed) - 4) + 5;
}
