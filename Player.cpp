#include "Player.h"
#include<QKeyEvent>
#include<iostream>
#include<GameWindow.h>
#include<Vehicle.h>
#include<QDateTime>
#include<qstring.h>
#include<Lane.h>
#include<Score.h>

Player::Player(GameWindow * game): gameWindow(game)
{
    setPixmap(QPixmap(":/images/zaba_gotowa.png"));
    setPos(388,567);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setData(0,GameWindow::itemType::frog);
    setData(1,alive);
    setFocus();

    gameWindow->addToScene(this);

    collDetectionTimer = std::make_unique<QTimer>();
    QObject::connect(collDetectionTimer.get(),SIGNAL(timeout()), this, SLOT(collisionDetection()));
    collDetectionTimer.get()->start(50);

    lives = 3;
    hearts = std::make_unique<QGraphicsPixmapItem>();
    hearts.get()->setPixmap(QPixmap(":/images/life3.png"));
    hearts.get()->setPos(10,1);
    gameWindow->addToScene(hearts.get());

    jumpSound = std::make_unique<QMediaPlayer>();
    deathSound = std::make_unique<QMediaPlayer>();
    switchSound = std::make_unique<QMediaPlayer>();
    endSound = std::make_unique<QMediaPlayer>();

    jumpSound.get()->setMedia(QUrl("qrc:/sounds/jump.wav"));
    jumpSound.get()->setVolume(1);
    deathSound.get()->setMedia(QUrl("qrc:/sounds/rozjechanie.wav"));
    deathSound.get()->setVolume(1);
    switchSound.get()->setMedia(QUrl("qrc:/sounds/switch.wav"));
    switchSound.get()->setVolume(5);
    endSound.get()->setMedia(QUrl("qrc:/sounds/death.wav"));
    endSound.get()->setVolume(1);
}

void Player::keyPressEvent(QKeyEvent *event)   // controls
{
    if(!event->isAutoRepeat())
    {
        if(!(gameWindow->isItemVisible(GameWindow::itemType::menuStart) ||
             gameWindow->isItemVisible(GameWindow::itemType::menuPause) ||
             gameWindow->isItemVisible(GameWindow::itemType::menuEnd) ||
             data(1) == dead))    //controls outside the menu
        {
            switch (event->key())
            {
            case Qt::Key_Left:
                if(pos().x() > 24)
                    setPos(x() - 24, y());
                jumpSound.get()->setPosition(0);
                jumpSound->play();
                break;
            case Qt::Key_Right:
                if(pos().x() < 755)
                    setPos(x() + 24, y());
                jumpSound.get()->setPosition(0);
                jumpSound->play();
                break;
            case Qt::Key_Up:
                if(pos().y() > 0)
                    setPos(x(), y() - 24);
                jumpSound.get()->setPosition(0);
                jumpSound->play();
                if(int(pos().y()) < 0)
                    levelUp();
                break;
            case Qt::Key_Down:
                if(pos().y() < 567)
                    setPos(x(), y() + 24);
                jumpSound.get()->setPosition(0);
                jumpSound->play();
                break;
            case Qt::Key_Escape:
                gameWindow->displayMenu(GameWindow::itemType::menuPause);
                break;
            }
        }

        else if (data(1) != dead)  //controls in the menu
        {
            switch (event->key())
            {
            case Qt::Key_Up:
                gameWindow->moveCursor(GameWindow::direction::up);
                switchSound.get()->setPosition(0);
                switchSound->play();
                break;
            case Qt::Key_Down:
                gameWindow->moveCursor(GameWindow::direction::down);
                switchSound.get()->setPosition(0);
                switchSound->play();
                break;
            case Qt::Key_Escape:
                gameWindow->removeMenu();
                break;
            case Qt::Key_Return:
                if(gameWindow->isItemVisible(GameWindow::itemType::menuStart))
                {
                    gameWindow->removeMenu();
                    switch(gameWindow->getCursorPosition())
                    {
                    case 1: //start
                        break;
                    case 2: //best scores
                        Score::LoadScores();
                        gameWindow->displayMenu(GameWindow::menuStart);
                        break;
                    case 3: //exit
                        gameWindow->close();
                        break;
                    }
                }
                else if(gameWindow->isItemVisible(GameWindow::itemType::menuPause))
                {
                    gameWindow->removeMenu();
                    switch(gameWindow->getCursorPosition())
                    {
                    case 1: //resume game
                        break;
                    case 2: //return to main menu
                        gameWindow->displayMenu(GameWindow::itemType::menuStart);
                        restart();
                        Score::resetLevel();
                        break;
                    case 3: //exit
                        gameWindow->close();
                        break;
                    }
                }
                else if(gameWindow->isItemVisible(GameWindow::itemType::menuEnd))
                {
                    gameWindow->removeMenu();
                    switch(gameWindow->getCursorPosition())
                    {
                    case 1: //play again
                        restart();
                        Score::resetLevel();
                        break;
                    case 2: //return to main menu
                        gameWindow->displayMenu(GameWindow::itemType::menuStart);
                        restart();
                        Score::resetLevel();
                        break;
                    case 3: //exit
                        gameWindow->close();
                        break;
                    }
                }
                break;
            }
        }
    }
}

void Player::decreaseLife()
{
    QString path;
    path = QString::fromStdString(":/images/life") + QString::number(lives) + QString::fromStdString(".png");
    hearts->setPixmap(QPixmap(path));
}

void Player::collisionDetection()
{
    QList<QGraphicsItem * > collidingItems = this->collidingItems();
    if(!(gameWindow->isItemVisible(GameWindow::itemType::menuStart)||
       gameWindow->isItemVisible(GameWindow::itemType::menuStart))
            && data(1) == alive)
    {
        for(int i=0; i<collidingItems.size();i++)
        {            
            if(collidingItems[i]->data(0) == GameWindow::itemType::vehicle)
            {
                deathSound.get()->play();
                this->setPos(this->x()-5, this->y()); // so make the new axis of symmetry match the previous pixmap's
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
    else if(lives == 0 &&
            QDateTime::currentMSecsSinceEpoch() - timeOfDeath < 70)      /* resetting difficulty before spawning the Player to
                                                                         allow the slowed down cars to fill the scene*/
    {
        endSound.get()->play();
        Lane::resetDifficulty();
    }
    else if(data(1) == dead && lives == 0 &&
            QDateTime::currentMSecsSinceEpoch() - timeOfDeath > 3000)
    {        
        Score::saveScore();
        gameWindow->displayMenu(GameWindow::itemType::menuEnd);
        restart();
    }
}

void Player::restart()
{
    lives = 3;
    hearts.get()->setPixmap(QPixmap(":/images/life3.png"));
    Score::resetLevel();
    setPixmap(QPixmap(":/images/zaba_gotowa.png"));
    setPos(388,567);
    this->setData(1,alive);
}

void Player::levelUp()
{
    Score::increaseScore();
    Lane::increaseDifficulty();
    setPos(388,567);
}
