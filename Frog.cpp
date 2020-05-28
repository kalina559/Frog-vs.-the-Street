#include "Frog.h"
#include<QKeyEvent>
#include<iostream>
#include<MainWindow.h>

Frog::Frog(MainWindow * game): mainWindow(game)
{
    this->setPixmap(QPixmap(":/images/zaba_gotowa.png"));
    this->setPos(388,567);
    //this->setData(0, "frog");    //this data allows to check whether MainWindow::menu.get() is visible on the scene
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    mainWindow->addToScene(this);
}

Frog::~Frog()
{
    std::cout<<"frog has been deleted"<<std::endl;
}

void Frog::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        if(!(mainWindow->isItemVisible(MainWindow::itemType::menuStart) ||
             mainWindow->isItemVisible(MainWindow::itemType::menuPause)))    //controls outside the MainWindow::menu.get()
        {
            switch (event->key()) {
            case Qt::Key_Left:
                if(pos().x() > 24)
                    setPos(x() - 24, y());
                break;

            case Qt::Key_Right:
                if(pos().x() < 755)
                    setPos(x() + 24, y());
                    break;

            case Qt::Key_Up:
                if(pos().y() > 0)
                    setPos(x(), y() - 24);
                break;

            case Qt::Key_Down:
                if(pos().y() < 567)
                    setPos(x(), y() + 24);
                break;
            case Qt::Key_Escape:
                mainWindow->displayMenu(MainWindow::itemType::menuPause);
                break;
            }
        }
        else  //  controls in the menu
        {
            switch (event->key()) {
            case Qt::Key_Up:
                mainWindow->moveCursor(MainWindow::direction::up);
                break;

            case Qt::Key_Down:
                mainWindow->moveCursor(MainWindow::direction::down);
                break;
            case Qt::Key_Escape:
                mainWindow->removeMenu();
                break;
            case Qt::Key_Return:
                mainWindow->removeMenu();
                break;
            }
        }
    }
}
