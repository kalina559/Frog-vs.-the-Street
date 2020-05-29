#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QGraphicsView>
#include<QTimer>
#include<QGraphicsPixmapItem>
#include<memory>

class MainWindow : public QGraphicsView
{
private:
    /*static*/ std::unique_ptr<QGraphicsScene> scene;
    /*static*/ std::unique_ptr<QGraphicsPixmapItem> menu;
    /*static*/ std::unique_ptr<QGraphicsPixmapItem> menuCursor;
    int cursorPosition;

public:
    enum itemType {menuStart, menuPause, menuEnd};
    enum direction {up, down};
    MainWindow();
    ~MainWindow();
    void startGame();
    void addToScene(QGraphicsPixmapItem *);      //allows to add graphics items to the scene
    void removeFromScene(QGraphicsPixmapItem *);
    void displayMenu(MainWindow::itemType);
    void removeMenu();
    void moveCursor(MainWindow::direction);
    bool isItemVisible(MainWindow::itemType);
    void restartGame();  //po kliknięciu 'powtórz' w menu pauzy/końcowym
    int getCursorPosition();
};

#endif // MAINWINDOW_H
