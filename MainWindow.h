#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QGraphicsView>
#include<QTimer>
#include<QGraphicsPixmapItem>
#include<memory>
#include<QGraphicsTextItem>
#include<fstream>



class MainWindow : public QGraphicsView
{
private:
    int cursorPosition;
    int points;
    int level;
    std::unique_ptr<QGraphicsScene> scene;
    std::unique_ptr<QGraphicsPixmapItem> menu;
    std::unique_ptr<QGraphicsPixmapItem> menuCursor;
    std::unique_ptr<QGraphicsTextItem> score;

public:
    enum itemType {menuStart, menuPause, menuEnd, frog, vehicle};
    enum direction {up, down};
    enum laneDirection {left, right};

    static std::unique_ptr<QTimer> timer;  // shared timer for Vehicles' movement
    QTimer * spawnTimer = nullptr;
    //static std::shared_ptr<QTimer> spawnTimer;  // shared timer for Vehicles' spawning


    MainWindow();

    ~MainWindow();

    void startGame();

    void addToScene(QGraphicsPixmapItem * item) //allows to add graphics items to the scene
    {
        scene->addItem(item);
    }
    void addToScene(QGraphicsTextItem * item)
    {
        scene->addItem(item);
    }

    void removeFromScene(QGraphicsPixmapItem *item)
    {
        scene->removeItem(item);
    }

    void displayMenu(MainWindow::itemType);

    void removeMenu();

    void moveCursor(MainWindow::direction);

    bool isItemVisible(MainWindow::itemType);

    void resetLevel();  //po kliknięciu 'powtórz' w menu pauzy/końcowym

    int getCursorPosition()
    {
        return cursorPosition;
    }

    void increaseScore();

    void resetScore()
    {
        points = 0;
        score.get()->setPlainText(QString("WYNIK: ") + QString::number(points));
    }

    void LoadScores();

    void saveScore();

};

#endif // MAINWINDOW_H
