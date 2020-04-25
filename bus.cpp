#include "bus.h"

Bus::Bus(){
    getBus();
}

void Bus::getStreets( QMap<QString, Street*> str ){
    this->streets = str;
}

QGraphicsEllipseItem *Bus::getBus(){
    return this->bus;
}

QVector<Street *> Bus::getRoute(){
    return( route );
}

void Bus::setRout(QString streetId){
    int size = route.size();
    if( size == 0 ){
        route.push_back( streets[ streetId ] );
    } else if( route[ size - 1 ]->equals( streets[ streetId ] ) ){
        route.push_back( streets[ streetId ] );
    } else {
        exit( 16 );
    }
}

QPointF Bus::SetPossition(){
    QPointF start;
    start.rx() =  route[ 0 ]->GetStreetStart().GetX() -2.5 ;
    start.ry() =  route[ 0 ]->GetStreetStart().GetY() -2.5 ;
    return start;
}
