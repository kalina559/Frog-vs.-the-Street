#ifndef LANE_H
#define LANE_H
#include<MainWindow.h>
#include<Vehicle.h>

class Lane: public QObject, public QGraphicsPixmapItem  /*Manages all vehicles on a particular lane.
                                                        Inherits from QObject so that it can connect to slots
                                                        Inherits from QGraphicsPixmapItem so that it can be
                                                        added to scene and later deleted*/
{


private:
    Q_OBJECT
    static MainWindow * mainWindow;
    //static QTimer * spawnTimer;  // shared timer for Vehicles' spawning
    int lanePosition;
    QList<Vehicle *> currentVehicles;
    std::unique_ptr<QTimer> deleteTimer;
    static int minSpeed;
    static int maxSpeed;
    int randomSpeed(int, int);
    MainWindow::laneDirection direction;
public:

    Lane(MainWindow *, MainWindow::laneDirection, int);
    ~Lane();
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
