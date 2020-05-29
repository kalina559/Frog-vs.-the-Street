#include "Lane.h"
#include<iostream>
#include<Vehicle.h>
Lane::Lane(MainWindow * game): mainWindow(game)
{
    //dodać jakąś zmienną mówiącą o tym który to pas, ta zmienna idzie potem też do Vehicle
}

void Lane::spawn()
{
    if(!mainWindow->isItemVisible(MainWindow::itemType::menuPause))
    {
        std::cout<<"lecimy tutaj"<<std::endl;
        Vehicle * vehicle = new Vehicle(this);  // deleted in Vehicle::move(), when it goes out of scene

        mainWindow->addToScene(vehicle);
    }
}
