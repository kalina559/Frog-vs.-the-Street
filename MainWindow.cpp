#include "MainWindow.h"
#include<iostream>
#include<Lane.h>
#include<QObject>
#include<QMessageBox>

std::unique_ptr<QTimer> MainWindow::timer = nullptr;
std::unique_ptr<QTimer> MainWindow::spawnTimer = nullptr;

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


    auto firstLane = new Lane(this, 93);   //adding all the lanes
    addToScene(firstLane);
    auto secondLane = new Lane(this, 164);
    addToScene(secondLane);

    timer = std::make_unique<QTimer>();
    timer.get()->start(50);    

    spawnTimer = std::make_unique<QTimer>();
    QObject::connect(spawnTimer.get(),SIGNAL(timeout()),firstLane,SLOT(spawn()));    //every lane uses the same timer to spawn cars
    QObject::connect(spawnTimer.get(),SIGNAL(timeout()),secondLane,SLOT(spawn()));
    spawnTimer.get()->start(3400);

    points = 0;
    level = 1;

    score = std::make_unique<QGraphicsTextItem>();
    QFont f("Helvetica",30,QFont::Bold);
    score.get()->setFont(f);
    score.get()->setPlainText(QString("WYNIK: ") + QString::number(points));
    score.get()->setDefaultTextColor(Qt::red);
    score.get()->setPos(280,-12);
    addToScene(score.get());
}

MainWindow::~MainWindow()  //called when window is closed
{

    std::cout << "~MainWindow has been called" << std::endl;
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

void MainWindow::increaseScore()
{
    points += level * 100;
    ++level;
    score.get()->setPlainText(QString("WYNIK: ") + QString::number(points));
    score->setPos(280,-12);
}

void MainWindow::LoadScores()
{
    QFont f("Helvetica", 15, QFont::Bold);
    score->setPos(50,-12);

    std::ifstream plik;                //odczyt najlepszych wyników
    plik.open("C:/Users/Kalin/QtProjekty/ProjektPJC/bestScores.txt");
    int firstScore;
    int secondScore;
    int thirdScore;

    std::string firstName;
    std::string secondName;
    std::string thirdName;

    plik>>firstName;
    plik>>firstScore;
    plik>>secondName;
    plik>>secondScore;
    plik>>thirdName;
    plik>>thirdScore;

//    if(this->points>firstScore)
//    {
//        thirdScore = secondScore;
//        thirdName = secondName;
//        secondScore = firstScore;
//        secondName = firstName;
//        firstScore  =this->points;
//        firstName =
//    }
//    else if(this->points>secondScore)
//    {
//        thirdScore = secondScore;
//        secondScore = this->points;
//    }
//    else if(this->points>thirdScore)
//    {
//        thirdScore = this->points;
//    }


    QMessageBox msg;
    msg.setText("Best scores: ");
    msg.setInformativeText(QString::fromStdString(firstName) + " " + QString::number(thirdScore) + "\n"
                           + QString::fromStdString(secondName) + " " + QString::number(secondScore) + "\n"
                           + QString::fromStdString(thirdName) + " " + QString::number(firstScore) + "\n" );
    msg.exec();

    plik.close();
    plik.clear();
//    std::ofstream p;       //zapis do pliku
//    p.open("C:/Users/Kalin/QtProjekty/ProjektPJC/bestScores.txt", std::ofstream::out|std::ofstream::trunc);
//    p<<firstScore<<std::endl;
//    p<<secondScore<<std::endl;
//    p<<thirdScore<<std::endl;
    //    plik.close();
}

void MainWindow::saveScore()
{

}


