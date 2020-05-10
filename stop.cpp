/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file stop.cpp
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief Informace o zastávkách
 */

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
