#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include<QGraphicsView>
#include<QTimer>
#include<QGraphicsPixmapItem>
#include<memory>
#include<QGraphicsTextItem>
#include<fstream>
#include<QMediaPlaylist>
#include<QMediaPlayer>
/** @brief Responsible for the visual side of the game.
    */
class GameWindow : public QGraphicsView
{
    int cursorPosition; /**< Stores the current position of menu cursor.*/
    static std::unique_ptr<QGraphicsScene> scene; /**< Game is displayed here.*/
    std::unique_ptr<QGraphicsPixmapItem> menu; /**< Holds menu pixmap.*/
    std::unique_ptr<QGraphicsPixmapItem> menuCursor /**< Holds menu cursor pixmap.*/;
    std::unique_ptr<QGraphicsTextItem> gameScore; /**< Holds gameScore text.*/
    std::unique_ptr<QMediaPlaylist> playlist; /**< Holds game playlist. \details Used to play music in a loop*/
    std::unique_ptr<QMediaPlayer> music; /**< Holds music used in playlist*/

public:
    /**
     * @brief Used to distinguish different QGraphicPixmapItems visible in the scene.
     * \details QGraphicPixmapItem->data(0) is set to a selected value of this enum.
     */
    enum itemType
    {
        menuStart, /**< Corresponds to start menu*/
        menuPause, /**< Corresponds to pause menu*/
        menuEnd, /**< Corresponds to end menu*/
        frog, /**< Corresponds to instances of Player class */
        vehicle /**< Corresponds to instances of Vehicle class*/
    };
    /**
     * @brief Used to distinguish the direction of menu cursor movement.
     */
    enum direction
    {
        up, /**< Corresponds to the upward movement*/
        down /**< Corresponds to  the downward movement*/
    };
    /**
     * @brief Used to distinguish the direction of vehicles' movement on the lanes.
     */
    enum laneDirection
    {
        left, /**< Corresponds to the leftward movement*/
        right   /**< Corresponds to the rightward movement*/
    };
    static std::unique_ptr<QTimer> timer; /**< Holds a static QTimer.
\details Used by instances of Vehicle class as a signal connected to slot Vehicle::move()*/
    QTimer * spawnTimer = nullptr; /**< Pointer to a QTimer.
\details Used by instances of Lane class as a signal connected to slot Lane::spawn()*/
    /**
     * @brief GameWindow constructor.
     * \details Class members are initialized here. Scene's settings are set
     * and start menu is displayed.
            */
    GameWindow();
/**
 * @brief GameWindow destructor.
 * \details Deletes spawnTimer.
  */
    ~GameWindow();
/**
 * @brief Adds QGraphicsPixmapItem items to the scene.
 * @param item Added item
  */
    void addToScene(QGraphicsPixmapItem * item)
    {
        scene->addItem(item);
    }
/**
 * @brief Adds QGraphicsTextItem items to the scene.
 * @param item Added item
  */
    static void addToScene(QGraphicsTextItem * item)
    {
        scene->addItem(item);
    }
/**
 * @brief Removes QGraphicsPixmapItem items from scene.
 * @param item Removed item
 */
    void removeFromScene(QGraphicsPixmapItem *item)
    {
        scene->removeItem(item);
    }
/**
 * @brief Adds selected menu to the scene.
 * @param type Type of the menu
  */
    void displayMenu(GameWindow::itemType type);
/**
 * @brief Removes selected menu and menu cursor from the scene.
  */
    void removeMenu()
    {
        scene->removeItem(menu.get());
        scene->removeItem(menuCursor.get());
    }
    /**
     * @brief Changes the position of the menu cursor member.
     * @param dir Direction of the movement
     */
    void moveCursor(GameWindow::direction dir);

    /**
    * @brief Checks if item of selected itemType is visible in the scene.
    * @param itemsName Type of the item
    * @return True if item is visible, false if not.
    */
    static bool isItemVisible(GameWindow::itemType itemsName);

    /**
     * @brief Returns the current position of menu cursor.
     * @return 1, 2 or 3
     */
    int getCursorPosition()
    {
        return cursorPosition;
    }
};

#endif // GameWindow_H
