#ifndef PLAYER_H
#define PLAYER_H
#include<QGraphicsPixmapItem>
#include<GameWindow.h>
/**
 * @brief Responsible for the player - game interaction - moving the game's character and moving in the menu.
 * \details Its members change as a result of player's activity.
 */
class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    long long timeOfDeath; /**< @brief Keeps the result of QDateTime::currentMSecsSinceEpoch() called when Player class instance
collides with Vehicle class instance.
\details Used to delay the player's respawn.*/

    int lives; /**< Number of lives left.*/
    std::unique_ptr<QGraphicsPixmapItem> hearts; /**< Holds the pixmap with the current number of lives.*/
    std::unique_ptr<QTimer> collDetectionTimer; /**< Holds a QTimer.
\details Used by Player class instance as a signal connected to slot Player::collisionDetection().*/
    std::unique_ptr<QMediaPlayer> jumpSound; /**< Holds the sound of frog's jump.*/
    std::unique_ptr<QMediaPlayer> deathSound; /**< Holds the sound of frog's death.*/
    std::unique_ptr<QMediaPlayer> switchSound; /**< Holds the sound of switching options in menu.*/
    std::unique_ptr<QMediaPlayer> endSound; /**< Holds the sound of the end of the game.*/
    /**
     * @brief Restarts the game.
     * \details Sets lives member to initial value and calls Scor::resetLevel()
     */
    void restart();
    /**
     * @brief Increases difficulty and score.
     */
    void levelUp();
    /**
     * @brief State of the Player class instance.
     */
    enum state
    {
        dead, /**< Corresponds to the frog being dead.*/
        alive/**< Corresponds to the frog being alive.*/
    };
public:
    GameWindow * gameWindow; /**< GameWindow class instance, that the Player class instance is assigned to.*/
    /**
     * @brief Player constructor.
     * @param game GameWindow class instance, that the Player class instance is assigned to.
     */
    Player(GameWindow *);
    /**
     * @brief Used to control the Player class instance and to move around in the menus.
     */
    void keyPressEvent(QKeyEvent * event);
    /**
     * @brief Used to change the hearts member.
     * \details Sets hearts.get().pixmap() to a pixmap displaying the current number of lives.
     */
    void decreaseLife();
public slots:
    /**
     * @brief Checks if the Player class instance collides with any Vehicle class instance.
     */
    void collisionDetection();
};

#endif // Player_H
