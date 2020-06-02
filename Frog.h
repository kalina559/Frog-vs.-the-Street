#ifndef FROG_H
#define FROG_H
#include<QGraphicsPixmapItem>
#include<MainWindow.h>
class Frog: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    MainWindow * mainWindow;
    long long timeOfDeath;
    bool paused;
    int lives;  //number of lives, max 3
    std::unique_ptr<QGraphicsPixmapItem> hearts;
    std::unique_ptr<QTimer> collDetectionTimer;
    std::unique_ptr<QMediaPlayer> jumpSound;
    std::unique_ptr<QMediaPlayer> deathSound;
    std::unique_ptr<QMediaPlayer> switchSound;
    std::unique_ptr<QMediaPlayer> endSound;
    void restart();
    void levelUp();
    enum state { dead, alive};
public:
    Frog(MainWindow *);
    ~Frog(){}
    void keyPressEvent(QKeyEvent * event); //sterowanie żabą i w menu
    void decreaseLife();
public slots:
    void collisionDetection();
};

#endif // FROG_H
