#include "Score.h"
#include<QMessageBox>
#include<QInputDialog>
#include<QGraphicsTextItem>
#include<iostream>
GameWindow * Score::gameWindow = nullptr;
QGraphicsTextItem * Score::gameScore = nullptr;
int Score::level = 1;
int Score::points = 0;
Score::Score(GameWindow * game, QGraphicsTextItem * text)
{
    gameWindow = game;
    gameScore = text;
    QFont f("Helvetica",30,QFont::Bold);
    gameScore->setFont(f);
    gameScore->setPlainText(QString("Score: ") + QString::number(points));
    gameScore->setDefaultTextColor(Qt::red);
    gameScore->setPos(280,-12);
    GameWindow::addToScene(gameScore);
}

void Score::increaseScore()
{
        points += level * 100;
        ++level;
        gameScore->setPlainText(QString("Score: ") + QString::number(points));
        gameScore->setPos(280,-12);
}

void Score::LoadScores()
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

void Score::saveScore()
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
        QString playerName = (QInputDialog::getText(Score::gameWindow,"Save","Please write your name"));

        for(int i = 0; i <10; ++i)
        {
            if(points > scores[i])
            {
                names.insert(i, playerName.toStdString());
                scores.insert(i, points);
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
