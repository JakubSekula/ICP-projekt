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
    QMap<QString, Street*> streets;
    QVector<Street*> route;
    QString name;
    QString id;
    float posX;
    float posY;
    float xStep;
    float yStep;
    bool switcher = false;

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

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void valueChanged(int newValue);
};

#endif // BUS_H
