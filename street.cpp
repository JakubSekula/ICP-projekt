#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <QString>
#include "coordinate.h"
#include "street.h"
#include <QDebug>

Street::Street( QString id, QString name, coordinate c1, coordinate c2 ){
    this->name = name;
    this->id = id;
    coordinates.push_back( c1 );
    coordinates.push_back( c2 );
}

QString Street::GetStreetID(){
    return name;
}

QString Street::GetStreetName(){
    return name;
}

coordinate Street::GetStreetStart(){
    return( coordinates.front() );
}

coordinate Street::GetStreetEnd(){
    return( coordinates.back() );
}

void Street::AddStop( stop* stop ){
    this->s1 = stop;
}

stop* Street::getStop(){
    if( this->s1 == NULL ){
        return NULL;
    } else {
        CountMiddle( GetStreetStart(), GetStreetEnd() );
        return s1;
    }
}

void Street::CountMiddle( coordinate c1, coordinate c2 ){
    int startX = c1.GetX();
    int startY = c1.GetY();
    int endX = c2.GetX();
    int endY = c2.GetY();

    int midX = 0;
    int midY = 0;

    int XDifference = endX - startX;
    int YDifference = endY - startY;

    midX = abs( XDifference ) / 2;

    midY = abs( YDifference ) / 2;

    if( startX > endX ){
        midX = endX + midX;
    } else {
        midX = startX + midX;
    }

    if( startY > endY ){
        midY = endY + midY;
    } else {
        midY = startY + midY;
    }

    //qDebug() << midX;
    //qDebug() << midY;

    this->middle = new coordinate( midX, midY );
}

coordinate* Street::GetMiddle(){
    return this->middle;
}
