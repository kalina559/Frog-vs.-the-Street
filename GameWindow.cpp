#include "GameWindow.h"
#include<iostream>
#include<Lane.h>
#include<QObject>
#include<QMessageBox>
#include<QInputDialog>
#include<Score.h>

std::unique_ptr<QTimer> GameWindow::timer = nullptr;
std::unique_ptr<QGraphicsScene> GameWindow::scene = nullptr;
GameWindow::GameWindow()
{
    srand( static_cast<unsigned int>(time(nullptr)));
    scene = std::make_unique<QGraphicsScene>();
    menu = std::make_unique<QGraphicsPixmapItem>();
    menuCursor = std::make_unique<QGraphicsPixmapItem>();

    scene = std::make_unique<QGraphicsScene>(new QGraphicsScene);
    scene->setSceneRect(0, 0, 800, 600);
    setBackgroundBrush(QBrush(QImage(":/resources/images/tlopaint.png")));
    setScene(scene.get());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    setMinimumSize(200,200);

    GameWindow::displayMenu(GameWindow::itemType::menuStart);

    spawnTimer = new QTimer();

    auto firstLane = new Lane(this, GameWindow::laneDirection::left, 93);   //adding all the lanes
    addToScene(firstLane);
    auto secondLane = new Lane(this, GameWindow::laneDirection::left, 164);
    addToScene(secondLane);
    auto thirdLane = new Lane(this, GameWindow::laneDirection::left, 235);
    addToScene(thirdLane);
    auto fourthLane = new Lane(this, GameWindow::laneDirection::right, 365);   //adding all the lanes
    addToScene(fourthLane);
    auto fifthLane = new Lane(this, GameWindow::laneDirection::right, 437);
    addToScene(fifthLane);
    auto sixthLane = new Lane(this, GameWindow::laneDirection::right, 505);
    addToScene(sixthLane);

    timer = std::make_unique<QTimer>();
    timer.get()->start(50);    

    gameScore = std::make_unique<QGraphicsTextItem>();
    auto score = std::make_unique<Score>(this, gameScore.get());    //instance of a helper class

    playlist = std::make_unique<QMediaPlaylist>();           //usuniete
    playlist.get()->addMedia(QUrl("qrc:/resources/sounds/muzyka.wav"));
    playlist.get()->setPlaybackMode(QMediaPlaylist::Loop);
    music = std::make_unique<QMediaPlayer>();
    music.get()->setPlaylist(playlist.get());
    music.get()->setVolume(1);
    music.get()->play();
}

GameWindow::~GameWindow()  //called when window is closed
{
    delete(spawnTimer);
}

void GameWindow::displayMenu(GameWindow::itemType type)
{
    menuCursor->setPixmap(QPixmap(":/resources/images/cursor.png"));
    menuCursor->setPos(400 - menuCursor->pixmap().width() / 2, 150);
    cursorPosition = 1;

    if(type == menuStart)
    {
        GameWindow::menu.get()->setPixmap(QPixmap(":/resources/images/menuStart.png"));
        menu.get()->setData(0,menuStart);
    }
    else if(type == menuPause)
    {
        menu.get()->setPixmap(QPixmap(":/resources/images/menuPause.png"));
        menu.get()->setData(0,menuPause);
    }
    else if(type == menuEnd)
    {
        menu.get()->setPixmap(QPixmap(":/resources/images/menuEnd.png"));
        menu.get()->setData(0,menuEnd);
    }
    menu->setPos(400 - menu->pixmap().width() / 2, 306 - menu->pixmap().height() / 2);
    addToScene(menu.get());
    addToScene(menuCursor.get());
}

void GameWindow::moveCursor(GameWindow::direction dir)
{
    if(dir == GameWindow::direction::up)
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

bool GameWindow::isItemVisible(GameWindow::itemType itemsName)   //checks whether an item of a certain type is visible on the scene
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


