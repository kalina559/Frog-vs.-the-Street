#include <QApplication>
#include<MainWindow.h>
#include<iostream>
#include<Frog.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    auto gra = new MainWindow();
    auto zaba = new Frog(gra);
    gra->setAttribute(Qt::WA_DeleteOnClose);
    gra->show();
    a.exec();

    return 0;
}
