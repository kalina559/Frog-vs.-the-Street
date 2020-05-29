#include "MainWindow.h"
#include<iostream>
#include<Lane.h>
#include<QObject>
//std::unique_ptr<QGraphicsScene> MainWindow::scene = nullptr;
//std::unique_ptr<QGraphicsPixmapItem> MainWindow::menu = nullptr;
//std::unique_ptr<QGraphicsPixmapItem> MainWindow::menuCursor = nullptr;

MainWindow::MainWindow()
{
    scene = std::make_unique<QGraphicsScene>();
    menu = std::make_unique<QGraphicsPixmapItem>();
    menuCursor = std::make_unique<QGraphicsPixmapItem>();

    scene->setSceneRect(0, 0, 800, 600);
    setBackgroundBrush(QBrush(QImage(":/images/tlopaint.png")));
    setScene(scene.get());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    MainWindow::displayMenu(MainWindow::itemType::menuStart);

    auto pas = new Lane(this);
    //scene->addItem(pas);
    auto spawnTimer = new QTimer();        //usuniete
    QObject::connect(spawnTimer,SIGNAL(timeout()),pas,SLOT(spawn()));
    spawnTimer->start(3400);
}

MainWindow::~MainWindow()  //called when window is closed
{
    std::cout << "~MainWindow has been called" << std::endl;
}

void MainWindow::addToScene(QGraphicsPixmapItem * item)
{
    std::cout<<"addtoscene"<<std::endl;
    scene->addItem(item);
}

void MainWindow::removeFromScene(QGraphicsPixmapItem *item)
{
    std::cout<<"removefromscene"<<std::endl;
    scene->removeItem(item);
}

void MainWindow::displayMenu(MainWindow::itemType type)
{
    menuCursor->setPixmap(QPixmap(":/images/cursor.png"));
    menuCursor->setPos(400 - menuCursor->pixmap().width() / 2, 150);
    cursorPosition = 1;

    if(type == menuStart)
    {
        MainWindow::menu.get()->setPixmap(QPixmap(":/images/menuStart.png"));
        menu.get()->setData(0,menuStart);
    }
    else if(type == menuPause)
    {
        menu.get()->setPixmap(QPixmap(":/images/menuPause.png"));
        menu.get()->setData(0,menuPause);
    }
    else
    {
        std::cout<<"nie pykło"<<std::endl;
    }    
    menu->setPos(400 - menu->pixmap().width() / 2, 306 - menu->pixmap().height() / 2);
    addToScene(menu.get());
    addToScene(menuCursor.get());
}

void MainWindow::removeMenu()
{
    scene->removeItem(menu.get());
    scene->removeItem(menuCursor.get());
}

void MainWindow::moveCursor(MainWindow::direction dir)
{
    if(dir == MainWindow::direction::up)
    {
        if(cursorPosition == 1)
        {
            cursorPosition = 3;
        }
        else
        {
            --cursorPosition;
        }        
    }
    else
    {
        if(cursorPosition == 3)
        {
            cursorPosition = 1;
        }
        else
        {
            ++cursorPosition;
        }        
    }
    menuCursor->setY(45 + cursorPosition * 105);
}

bool MainWindow::isItemVisible(MainWindow::itemType itemsName)   //checks whether an item of a certain type is visible on the scene
{
    foreach (auto item, scene->items())
    {
        if(item->data(0) == itemsName)
        {
            return true;
        }
    }
    return false;
}

int MainWindow::getCursorPosition()
{
    return cursorPosition;
}

