#include "stop.h"

QRectF stop::boundingRect() const
{
    return QRectF( 0, 0, 5, 5 );
}

void stop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush( Qt::blue );
    QPen pen( brush, 4 );
    painter->setPen( pen );
    painter->drawEllipse( rec );
}

stop::stop(){

}

void stop::initialize( QString identif, QString name )
{
    this->id = identif;
    this->name = name;
    return;
}

QString stop::getName(){
    return this->name;
}

QString stop::getID(){
    return this->id;
}

void stop::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    qDebug() << this->name;
    qDebug() << this->id;
}
