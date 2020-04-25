#ifndef BUS_H
#define BUS_H

#include <QDebug>
#include <QMap>
#include <QGraphicsEllipseItem>
#include "street.h"
#include <cmath>


class Bus
{

private:
    Street* current;
    int currenti;
    QMap<QString, Street*> streets;
    QVector<Street*> route;
    QString name;
    float posX;
    float posY;
    float xStep;
    float yStep;
    bool switcher = false;

public:
    QGraphicsEllipseItem* bus{nullptr};
    Bus();
    void getStreets( QMap<QString, Street*> str );
    QGraphicsEllipseItem* getBus();
    QVector<Street *> getRoute();
    void setRout( QString streetId );
    void NameIt( QString streetName );
    QPointF GetPossition();
    void setBus( QGraphicsEllipseItem *bus );
    QPointF getPos();
    void nextPos();

};

#endif // BUS_H
