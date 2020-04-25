#ifndef BUS_H
#define BUS_H

#include <QDebug>
#include <QMap>
#include <QGraphicsEllipseItem>
#include "street.h"


class Bus
{

private:
    QMap<QString, Street*> streets;
    QVector<Street*> route;

public:
    QGraphicsEllipseItem* bus;
    Bus();
    void getStreets( QMap<QString, Street*> str );
    QGraphicsEllipseItem* getBus();
    QVector<Street *> getRoute();
    void setRout( QString streetId );
    QPointF SetPossition();

};

#endif // BUS_H
