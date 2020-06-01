#ifndef LANE_H
#define LANE_H
#include<MainWindow.h>
#include<Vehicle.h>

class Lane: public QObject, public QGraphicsPixmapItem  /*Manages all vehicles on a particular lane.
                                                        Inherits from QObject so that it can connect to slots
                                                        Inherits from QGraphicsPixmapItem so that it can be
                                                        added to scene and later deleted*/
{
    Q_OBJECT
    MainWindow * mainWindow;
    int lanePosition;
    QList<Vehicle *> currentVehicles;
    std::unique_ptr<QTimer> deleteTimer;
    int minSpeed;
    int randomSpeed();

public:
    Lane(MainWindow *, int);
    ~Lane();
    int getLanePosition()
    {
        return lanePosition;
    }

public slots:
    void spawn();
    void deleteOutOfScene();
};

#endif // LANE_H
