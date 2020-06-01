#include "Frog.h"
#include<QKeyEvent>
#include<iostream>
#include<MainWindow.h>
#include<Vehicle.h>
#include<QDateTime>
#include<qstring.h>

Frog::Frog(MainWindow * game): mainWindow(game)
{
    setPixmap(QPixmap(":/images/zaba_gotowa.png"));
    setPos(388,567);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setData(0,MainWindow::itemType::frog);
    setData(1,alive);
    setFocus();

    mainWindow->addToScene(this);

    collDetectionTimer = std::make_unique<QTimer>();
    QObject::connect(collDetectionTimer.get(),SIGNAL(timeout()), this, SLOT(collisionDetection()));
    collDetectionTimer.get()->start(50);

    lives = 3;
    hearts = std::make_unique<QGraphicsPixmapItem>();
    hearts.get()->setPixmap(QPixmap(":/images/life3.png"));
    hearts.get()->setPos(10,1);
    mainWindow->addToScene(hearts.get());

    paused = false;
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
             mainWindow->isItemVisible(MainWindow::itemType::menuPause) ||
             mainWindow->isItemVisible(MainWindow::itemType::menuEnd) ||
             data(1) == dead))    //controls outside the menu
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
                if(int(pos().y()) < 0)
                    levelUp();
                break;

            case Qt::Key_Down:
                if(pos().y() < 567)
                    setPos(x(), y() + 24);
                break;
            case Qt::Key_Escape:
                mainWindow->displayMenu(MainWindow::itemType::menuPause);
                paused = true;
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
                        mainWindow->LoadScores();
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
                        restart();
                        mainWindow->resetScore();
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

void Frog::decreaseLife()
{

    QString path;

    path = QString::fromStdString(":/images/life") + QString::number(lives) + QString::fromStdString(".png");
    hearts->setPixmap(QPixmap(path));
}

void Frog::collisionDetection()
{
    QList<QGraphicsItem * > collidingItems = this->collidingItems();
    if(!(mainWindow->isItemVisible(MainWindow::itemType::menuStart)||
       mainWindow->isItemVisible(MainWindow::itemType::menuStart))
            && data(1) == alive)
    {
        for(int i=0; i<collidingItems.size();i++)
        {
            if(collidingItems[i]->data(0) == MainWindow::itemType::vehicle)
            {
                this->setPos(this->x()-5, this->y());                    //po to żeby oś symetrii zdjecia byla w tym samym miejscu
                this->setPixmap(QPixmap(":/images/przejechana.png"));
                this->setData(1,dead);
                timeOfDeath = QDateTime::currentMSecsSinceEpoch();
                --lives;
                decreaseLife();

            }
        }
    }
    else if(data(1) == dead && lives > 0 &&
            QDateTime::currentMSecsSinceEpoch() - timeOfDeath > 1000)
    {
        setPixmap(QPixmap(":/images/zaba_gotowa.png"));
        this->setData(1,alive);
        setPos(388,567);
    }
    else if(data(1) == dead && lives == 0 &&
            QDateTime::currentMSecsSinceEpoch() - timeOfDeath > 2000)
    {
        restart();
    }

}

void Frog::restart()
{
    lives = 3;
    hearts.get()->setPixmap(QPixmap(":/images/life3.png"));
    setPixmap(QPixmap(":/images/zaba_gotowa.png"));
    this->setData(1,alive);
    setPos(388,567);
}

void Frog::levelUp()
{
    mainWindow->increaseScore();
    setPos(388,567);
}
