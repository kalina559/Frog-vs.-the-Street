#include "MainWindow.h"
#include<iostream>
#include<Lane.h>
#include<QObject>
#include<QMessageBox>
#include<QInputDialog>

std::unique_ptr<QTimer> MainWindow::timer = nullptr;

MainWindow::MainWindow()
{
    srand( static_cast<unsigned int>(time(nullptr)));
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

    spawnTimer = new QTimer();

    auto firstLane = new Lane(this, MainWindow::laneDirection::left, 93);   //adding all the lanes
    addToScene(firstLane);
    auto secondLane = new Lane(this, MainWindow::laneDirection::left, 164);
    addToScene(secondLane);
    auto thirdLane = new Lane(this, MainWindow::laneDirection::left, 235);
    addToScene(thirdLane);
    auto fourthLane = new Lane(this, MainWindow::laneDirection::right, 365);   //adding all the lanes
    addToScene(fourthLane);
    auto fifthLane = new Lane(this, MainWindow::laneDirection::right, 437);
    addToScene(fifthLane);
    auto sixthLane = new Lane(this, MainWindow::laneDirection::right, 505);
    addToScene(sixthLane);

    timer = std::make_unique<QTimer>();
    timer.get()->start(50);    

    points = 0;
    level = 1;

    score = std::make_unique<QGraphicsTextItem>();
    QFont f("Helvetica",30,QFont::Bold);
    score.get()->setFont(f);
    score.get()->setPlainText(QString("WYNIK: ") + QString::number(points));
    score.get()->setDefaultTextColor(Qt::red);
    score.get()->setPos(280,-12);
    addToScene(score.get());

    playlist = std::make_unique<QMediaPlaylist>();           //usuniete
    playlist.get()->addMedia(QUrl("qrc:/sounds/muzyka.wav"));
    playlist.get()->setPlaybackMode(QMediaPlaylist::Loop);
    music = std::make_unique<QMediaPlayer>();
    music.get()->setPlaylist(playlist.get());
    music.get()->setVolume(1);
    music.get()->play();
}

MainWindow::~MainWindow()  //called when window is closed
{
    delete(spawnTimer);
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
    else if(type == menuEnd)
    {
        menu.get()->setPixmap(QPixmap(":/images/menuEnd.png"));
        menu.get()->setData(0,menuEnd);
    }
    menu->setPos(400 - menu->pixmap().width() / 2, 306 - menu->pixmap().height() / 2);
    addToScene(menu.get());
    addToScene(menuCursor.get());
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

void MainWindow::increaseScore()
{
    points += level * 100;
    ++level;
    score.get()->setPlainText(QString("WYNIK: ") + QString::number(points));
    score->setPos(280,-12);
}

void MainWindow::LoadScores()
{
    std::ifstream file;                //odczyt najlepszych wyników
    file.open(std::string(PROJECT_PATH) + "bestScores.txt");

    int score = 0;
    std::string name;

    QList<int> scores;
    QList<std::string> names;

    while(file >> name >> score)
    {
        scores.push_back(score);
        names.push_back(name);
    }

    QString text = nullptr;
    while(!scores.empty())
    {
        text += QString::fromStdString(names.front()) + " " + QString::number(scores.front()) + "\n";
        scores.pop_front();
        names.pop_front();
    }
    QMessageBox msg;
    msg.setWindowTitle("Records");
    msg.setText("Best scores: ");
    msg.setInformativeText(text);
    msg.exec();

    file.close();
    file.clear();
}

void MainWindow::saveScore()
{
    std::ifstream file;                //odczyt najlepszych wyników
    file.open(std::string(PROJECT_PATH) + "bestScores.txt");

    int score = 0;
    std::string name;

    QList<int> scores;
    QList<std::string> names;

    while(file >> name >> score)
    {
        scores.push_back(score);
        names.push_back(name);
    }

    if(points > scores.back())
    {
        QString playerName = (QInputDialog::getText(this,"Save","Please write your name"));

        for(int i = 0; i <10; ++i)
        {            
            if(this->points > scores[i])
            {
                names.insert(i, playerName.toStdString());
                scores.insert(i, this->points);
                scores.pop_back();
                names.pop_back();
                break;
            }
        }
        QString text = nullptr;

        for(int i = 0; i < 10; ++i)
        {
            text += QString::fromStdString(names[i]) + " " + QString::number(scores[i]) + "\n";
        }

        QMessageBox msg;
        msg.setWindowTitle("Records");
        msg.setText("Best scores: ");
        msg.setInformativeText(text);
        msg.exec();

        file.close();
        file.clear();
        std::ofstream p;       //zapis do fileu
        p.open(std::string(PROJECT_PATH) + "bestScores.txt", std::ofstream::out|std::ofstream::trunc);

        while(!scores.empty())
        {
            p<<names.front()<<std::endl;
            p<<scores.front()<<std::endl;
            scores.pop_front();
            names.pop_front();
        }
        file.close();
        }
}


