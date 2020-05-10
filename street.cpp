#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <QString>
#include "coordinate.h"
#include "street.h"
#include <QDebug>

Street::Street( QString id, QString name, coordinate c1, coordinate c2 )
    : QGraphicsLineItem( c1.GetX(), c1.GetY(), c2.GetX(), c2.GetY() ){
    this->setPen( QPen( QColor(99, 214, 104), 1.5 ) );
    this->color = 1;
    this->name = name;
    this->id = id;
    coordinates.push_back( c1 );
    coordinates.push_back( c2 );
}

QString Street::GetStreetID(){
    return id;
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

    float midX = 0;
    float midY = 0;

    float XDifference = endX - startX;
    float YDifference = endY - startY;

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

    this->middle = new coordinate( midX, midY );
}

coordinate* Street::GetMiddle(){
    return this->middle;
}

bool Street::equals(Street* street){
    if( ( this->GetStreetEnd().GetX() == street->GetStreetStart().GetX() && this->GetStreetEnd().GetY() == street->GetStreetStart().GetY() ) ||
        ( this->GetStreetEnd().GetX() == street->GetStreetEnd().GetX() && this->GetStreetEnd().GetY() == street->GetStreetEnd().GetY() )){
        return true;
    } else if( ( this->GetStreetStart().GetX() == street->GetStreetEnd().GetX() && this->GetStreetStart().GetY() == street->GetStreetEnd().GetY() ) ||
               ( this->GetStreetStart().GetX() == street->GetStreetStart().GetX() && this->GetStreetStart().GetY() == street->GetStreetStart().GetY() ) ) {
        return true;
    } else {
        return false;
    }
}

bool Street::WhichWay( Street* street1, Street* street2 ){
    if( street1->GetStreetStart().GetX() == street2->GetStreetStart().GetX() && street1->GetStreetStart().GetY() == street2->GetStreetStart().GetY() ){
        return true;
    } else if ( street1->GetStreetStart().GetX() == street2->GetStreetEnd().GetX() && street1->GetStreetStart().GetY() == street2->GetStreetEnd().GetY() ){
        return true;
    } else {
        return false;
    }
}

void Street::mousePressEvent( QGraphicsSceneMouseEvent* event ){

    QColor col = this->pen().color();
    if(event->button() & Qt::LeftButton  && changeable){

        if(col == QColor(99, 214, 104)){
           this->setPen(QPen(QColor(255, 151, 77), 1.5));
            this->color = 2;
        }
        else if(col == QColor(255, 151, 77)){
            this->setPen(QPen(QColor(242, 60, 50), 1.5));
            this->color = 3;
        }
        else if(col == QColor(242, 60, 50)){
            this->setPen(QPen(QColor(99, 214, 104), 1.5));
            this->color = 1;
        }
    }
    else if (changeable){
        if(col == QColor(0,170,240)){
           emit setBackColor(this);
        }
        else{
            CountMiddle(GetStreetStart(), GetStreetEnd());
            emit isBlack(GetMiddle(), this);
        }
    }
}

