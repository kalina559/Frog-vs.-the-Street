#include "MainWindow.h"
#include<iostream>
#include<Interface.h>       //do usuniecia

std::unique_ptr<QGraphicsScene> MainWindow::scene = nullptr;
//std::unique_ptr<Frog> MainWindow::frog = nullptr;
std::unique_ptr<QGraphicsPixmapItem> MainWindow::menu = nullptr;
std::unique_ptr<QGraphicsPixmapItem> MainWindow::menuCursor = nullptr;

MainWindow::MainWindow()
{
    // create the scene
    scene = std::make_unique<QGraphicsScene>();
    //frog = std::make_unique<Frog>();
    menu = std::make_unique<QGraphicsPixmapItem>();
    menuCursor = std::make_unique<QGraphicsPixmapItem>();

    scene->setSceneRect(0, 0, 800, 600);
    setBackgroundBrush(QBrush(QImage(":/images/tlopaint.png")));
    setScene(scene.get());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    //scene->addItem(frog.get());

    //frog->setFlag(QGraphicsItem::ItemIsFocusable);
    //frog->setFocus();

    MainWindow::displayMenu(MainWindow::itemType::menuStart);
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
    menuCursor->setPixmap(QPixmap(":/images/opcja2.png"));
    menuCursor->setPos(400-menuCursor->pixmap().width()/2,135);

    if(type == menuStart)
    {
        MainWindow::menu.get()->setPixmap(QPixmap(":/images/menu.png"));
        std::cout<<"ostatni"<<std::endl;
        menu.get()->setPos(400 - menu.get()->pixmap().width()/2, 300- menu.get()->pixmap().height()/2);
        menu.get()->setData(0,menuStart);
    }
    else if(type == menuPause)
    {
        menu.get()->setPixmap(QPixmap(":/images/menupauzy.png"));
        menu.get()->setPos(400 - menu.get()->pixmap().width()/2, 300- menu.get()->pixmap().height()/2);
        menu.get()->setData(0,menuPause);
    }
    else
    {
        std::cout<<"nie pykło"<<std::endl;
    }    
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
        if(menuCursor->y() == 135)
        {
            menuCursor->setPos(24, 365);
        }
        else
        {
            menuCursor->setY(menuCursor->y() - 115);
        }
    }
    else
    {
        if(menuCursor->y() == 365)
        {
            menuCursor->setPos(24, 135);
        }
        else
        {
            menuCursor->setY(menuCursor->y() + 115);
        }
    }
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

