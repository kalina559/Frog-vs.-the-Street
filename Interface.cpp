#include"MainWindow.h"
#include "Interface.h"
#include<iostream>
#include<QKeyEvent>
//DO TESTOWANIA
Interface::Interface()
{
    this->setPixmap(QPixmap(":/images/life.png"));
    this->setPos(100,100);
    //std::cout << MainWindow::scene->isActive() << std::endl;
}

Interface::~Interface()
{
    std::cout<<"interface skasowany"<<std::endl;
}

