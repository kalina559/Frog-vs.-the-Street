#ifndef FROG_H
#define FROG_H
#include<QGraphicsPixmapItem>
#include<MainWindow.h>
class Frog: public QGraphicsPixmapItem
{
private:
    MainWindow * mainWindow;
    int lives;  //number of lives, max 3
    //QGraphicsPixmapItem * menu = new QGraphicsPixmapItem;  // pixmap item odpowiedzialny za różne menu
public:
    Frog(MainWindow *);
    ~Frog();
    void keyPressEvent(QKeyEvent * event); //sterowanie żabą i w menu
};

#endif // FROG_H
