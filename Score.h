#ifndef SCORE_H
#define SCORE_H
#include<Player.h>
/**
 * @brief Helper class used to perform operations on QGraphicsTextItem.
 */
class Score
{
    static int points; /**< Points value.*/
    static int level; /**< Level value.*/
    static GameWindow * gameWindow; /**< Static pointer to the GaneWindow class instance that initialized Score class instance.*/
    static QGraphicsTextItem * gameScore; /**< Static pointer to the QGraphicsTextItem class instance that the Score class instance operates on.*/
public:
    /**
     * @brief Score constructor
     * \details Assigns arguments' values to static pointers gameWindow and gameScore. Displays initial text on gameWindow->scene();
     * @param game GameWindow class instance that initialized Score class instance.
     * @param text QGraphicsTextItem class instance that the Score class instance operates on.
     */
    Score(GameWindow* game, QGraphicsTextItem* text);
    /**
     * @brief Adds points to the score and updates the gameScore member.
     */
    static void increaseScore();
    /**
     * @brief Sets level and points to initial values and updates the gameScore member.
     */
    static void resetLevel()
    {
        level = 1;
        points = 0;
        gameScore->setPlainText(QString("WYNIK: ") + QString::number(points));
    }
    /**
     * @brief Loads 10 best scores from a .txt file in the project path.
     */
    static void LoadScores();
    /**
     * @brief Saves a score in a .txt file in the project path.
     * \details Checks if the score was better than any of the top 10 scores in the .txt file. If so, it saves it and deletes the tenth best score.
     */
    static void saveScore();
};

#endif // SCORE_H
