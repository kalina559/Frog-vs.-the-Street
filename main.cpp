#include <QApplication>
#include<MainWindow.h>
#include<iostream>
#include<Frog.h>
#include<Lane.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    auto gameWindow = new MainWindow();
    auto player = new Frog(gameWindow);

    gameWindow->setAttribute(Qt::WA_DeleteOnClose);
    gameWindow->show();
    a.exec();

    return 0;
}
