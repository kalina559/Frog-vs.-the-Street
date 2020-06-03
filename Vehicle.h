#ifndef VEHICLE_H
#define VEHICLE_H
#include<QGraphicsPixmapItem>
#include<GameWindow.h>
#include<QObject>
/**
 * @brief Moves across the game's scene.
 * \details Player's goal is to avoid instances of this class.
 */
class Vehicle: public QObject, public QGraphicsPixmapItem     //inherits from QObject so that it can connect to slots
{
    Q_OBJECT
    int speed; /**< Speed of the Vehicle class instance.*/
    int position/**< Y - position on the game's scene, where Vehicle class instance will be spawned.*/;
    GameWindow::laneDirection direction /**< Decides which way the Vehicle class instance will move.*/;
public:
    /**
     * @brief Vehicle constructor.
     * \details Draws random pixmap for the Vehicle class instance and connects slot Vehicle::move() to GameWindow::timer.
     * @param dir Decides which way the Vehicle class instance will move.
     * @param position Y - position on the game's scene, where Vehicle class instance will be spawned.
     * @param sp Speed of the Vehicle class instance.
     */
    Vehicle(GameWindow::laneDirection, int, int);
    /**
     * @brief Return the speed of a Vehicle class instance.
     * @return Speed of a Vehicle class instance.
     */
    int getVehicleSpeed()
    {
        return speed;
    }
public slots:
    /**
     * @brief Moves a Vehicle class instance with a given speed.
     * \details Direction of the movement depends on the direction member.
     */
    void move();
};

#endif // VEHICLE_H
