#include "Lane.h"
#include<iostream>
#include<Vehicle.h>
#include<math.h>
#include <stdlib.h>
#include<time.h>

MainWindow * Lane::mainWindow = nullptr;
int Lane::minSpeed = 0;
int Lane::maxSpeed = 0;
Lane::Lane(MainWindow * game, MainWindow::laneDirection dir, int lane): lanePosition(lane), direction(dir)
{
    mainWindow = game;
    minSpeed = 5;
    maxSpeed = 10;
    deleteTimer = std::make_unique<QTimer>(new QTimer());
    connect(deleteTimer.get(),SIGNAL(timeout()), this, SLOT(deleteOutOfScene()));
    deleteTimer.get()->start(50);

    QObject::connect(mainWindow->spawnTimer,SIGNAL(timeout()),this,SLOT(spawn()));    //every lane uses the same timer to spawn cars
    mainWindow->spawnTimer->start(( 9100* 2 / minSpeed));
}

void Lane::increaseDifficulty()
{
    ++minSpeed;
    ++maxSpeed;
    mainWindow->spawnTimer->setInterval(( 9100 * 2 / (minSpeed)));
}

void Lane::resetDifficulty()
{
    minSpeed = 5;
    maxSpeed = 10;
    mainWindow->spawnTimer->setInterval(( 9100 * 2 / (minSpeed)));
}
void Lane::spawn()
{
    if(!mainWindow->isItemVisible(MainWindow::itemType::menuPause))
    {
        int speed = randomSpeed(minSpeed, maxSpeed);
        if(speed != -1)
        {
            Vehicle *  vehicle = new Vehicle(mainWindow, direction, lanePosition, speed);  // deleted in Vehicle::move(), when it goes out of scene
            currentVehicles.push_back(vehicle);
            mainWindow->addToScene(vehicle);
        }
    }
}
void Lane::deleteOutOfScene()
{
    if(currentVehicles.size() > 0)
    {
        switch(direction)
        {
        case MainWindow::laneDirection::left:
            if(currentVehicles.front()->pos().x() < - currentVehicles.front()->pixmap().width())
            {
                Vehicle * outOfScene = currentVehicles.front();
                currentVehicles.erase(currentVehicles.begin() + 0);
                delete(outOfScene);
            }
            break;
        case MainWindow::laneDirection::right:
            if(currentVehicles.front()->pos().x() > 800 + currentVehicles.front()->pixmap().width() )
            {
                Vehicle * outOfScene = currentVehicles.front();
                currentVehicles.erase(currentVehicles.begin() + 0);
                delete(outOfScene);
            }
            break;
        }
    }
}

int Lane::randomSpeed(int minSpeed, int maxSpeed)
{
    double max;
    if(currentVehicles.size() == 0)
    {
        max = maxSpeed;
    }
    else
    {
        switch(direction)
        {
        case MainWindow::laneDirection::left:
            max = floor((800 * currentVehicles.back()->getVehicleSpeed())/(currentVehicles.back()->pos().x()
                                                                          + currentVehicles.back()->pixmap().width()));
            break;
        case MainWindow::laneDirection::right:
            max = floor((800 * currentVehicles.back()->getVehicleSpeed() / (800 - currentVehicles.back()->x())));
            break;
        }
    }
    if(int(max) < minSpeed) //to avoid errors with rand()
    {
        return -1; //when this function returns -1, Lane::spawn() waits for one interval
    }
    else if(int(max) > maxSpeed)
    {
        max = maxSpeed;
    }
    return rand() % (int(max) - minSpeed + 1) + minSpeed;
}
