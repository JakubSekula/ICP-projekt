#include "stop.h"

/**
 * @brief stop::boundingRect Vytvori kruh, znacku zastavky
 * @return  Vracia objekt, kruh
 */
QRectF stop::boundingRect() const
{
    return QRectF( 0, 0, 5, 5 );
}

/**
 * @brief stop::paint Vykreslenie kruhu
 * @param painter
 * @param option
 * @param widget
 */
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

/**
 * @brief stop::initialize Nastavenie ID a mena zastavky
 * @param identif
 * @param name
 */
void stop::initialize( QString identif, QString name )
{
    this->id = identif;
    this->name = name;
    return;
}

/**
 * @brief stop::getName
 * @return Vrati meno zastavky
 */
QString stop::getName(){
    return this->name;
}

/**
 * @brief stop::getID
 * @return Vrati ID zastavky
 */
QString stop::getID(){
    return this->id;
}

void stop::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    qDebug() << this->name;
    qDebug() << this->id;
}
