#ifndef BUS_H
#define BUS_H

#include <QDebug>
#include <QMap>
#include <QObject>
#include <QGraphicsEllipseItem>
#include "street.h"
#include <cmath>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include "dialog.h"

class Bus : public QGraphicsItem
{

private:
    Street* current;
    int currenti;
    int currentStops = 0;
    QMap<QString, Street*> streets;
    QVector<Street*> route;
    QString name;
    QString id;
    float posX;
    float posY;
    float xStep;
    float yStep;
    bool switcher = false;
    QVector<QString> stopsOnRoute;
    QVector<int> additions;
    float countStreetLenght( Street* street );
    float speedCoef = 1;
    int stopnow = 0;
    int currentStop = 0;
    float diffx = 0;
    float diffy = 0;
    float step;
    float streetLength = 0;
    void countAdditions( float sx, float sy, float ex, float ey );
    float hypotenuse = 0;
    float rest = 0;
    bool useRest = false;
    bool stopAtStop = false;
    bool changeStop = false;
    int streetWithStop = 0;
    float countDistanceToStop();
    float length = 0;
    bool stationary = false;
    bool halflength = false;

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QGraphicsEllipseItem* bus{nullptr};
    Bus();
    void getStreets( QMap<QString, Street*> str );
    QGraphicsEllipseItem* getBus();
    QVector<Street *> getRoute();
    void setRout( QString streetId );
    void NameIt( QString streetName );
    void IdIt( QString ID );
    QPointF GetPossition();
    void setBus();
    QPointF getPos();
    void nextPos();
    QString getId();
    QString getName();
    QPointF getMiddle();
    void setStart( QString time );
    QString getStart();
    QString start;
    bool onmap = false;
    QString startTime;
    QVector<stop*> stops;
    void getStops();
    QVector<QVector<QString>>plannedStops;
    QMap<int,QVector<float>>test;
    int steps = 0;
    int now = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void valueChanged(int newValue);
};

#endif // BUS_H
