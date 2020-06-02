#ifndef LANE_H
#define LANE_H
#include<MainWindow.h>
#include<Vehicle.h>
//Manages all vehicles on a particular lane.
//Inherits from QObject so that it can connect to slots
//Inherits from QGraphicsPixmapItem so that it can be
//added to scene and later deleted
class Lane: public QObject, public QGraphicsPixmapItem
{
private:
    Q_OBJECT
    static MainWindow * mainWindow;
    static int minSpeed;
    static int maxSpeed;

    int lanePosition;
    int randomSpeed(int, int);
    QList<Vehicle *> currentVehicles;
    std::unique_ptr<QTimer> deleteTimer;
    MainWindow::laneDirection direction;
public:
    Lane(MainWindow *, MainWindow::laneDirection, int);

    ~Lane(){}

    int getLanePosition()
    {
        return lanePosition;
    }

    static void increaseDifficulty();

    static void resetDifficulty();

public slots:
    void spawn();

    void deleteOutOfScene();
};

#endif // LANE_H
