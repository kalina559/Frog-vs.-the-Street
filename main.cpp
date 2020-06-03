#include <QApplication>
#include<GameWindow.h>
#include<iostream>
#include<Player.h>
#include<Lane.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    auto gameWindow = new GameWindow();
    auto player = new Player(gameWindow);

    gameWindow->setAttribute(Qt::WA_DeleteOnClose);
    gameWindow->show();
    a.exec();

    return 0;
}
