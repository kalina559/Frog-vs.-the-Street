#include "Frog.h"
#include<QKeyEvent>
#include<iostream>
#include<MainWindow.h>

Frog::Frog(MainWindow * game): mainWindow(game)
{
    this->setPixmap(QPixmap(":/images/zaba_gotowa.png"));
    this->setPos(388,567);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    mainWindow->addToScene(this);
}

Frog::~Frog()
{
    std::cout<<"frog has been deleted"<<std::endl;
}

void Frog::keyPressEvent(QKeyEvent *event)   // controls
{
    if(!event->isAutoRepeat())
    {
        if(!(mainWindow->isItemVisible(MainWindow::itemType::menuStart) ||
             mainWindow->isItemVisible(MainWindow::itemType::menuPause)))    //controls outside the menu
        {
            switch (event->key())
            {
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
            switch (event->key())
            {
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
                if(mainWindow->isItemVisible(MainWindow::itemType::menuStart))
                {
                    mainWindow->removeMenu();
                    switch(mainWindow->getCursorPosition())
                    {
                    case 1:
                        //start
                        break;
                    case 2:
                        //best scores
                        break;
                    case 3:
                        //exit
                        mainWindow->close();
                        break;
                    }
                }
                else if(mainWindow->isItemVisible(MainWindow::itemType::menuPause))
                {
                    mainWindow->removeMenu();
                    switch(mainWindow->getCursorPosition())
                    {
                    case 1:
                        //resume game
                        break;
                    case 2:
                        //return to main menu
                        mainWindow->displayMenu(MainWindow::itemType::menuStart);
                        break;
                    case 3:
                        //exit
                        mainWindow->close();
                        break;
                    }
                }
                break;
            }
        }
    }
}
