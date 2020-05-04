#include "bus.h"

QRectF Bus::boundingRect() const{
    return QRectF( 0, 0, 5, 5 );
}

void Bus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush( Qt::red );
    QPen pen( brush, 3 );
    painter->setPen( pen );
    painter->drawEllipse( rec );
}

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

void Bus::setRout( QString streetId ){
    int size = route.size();
    if( size == 0 ){
        route.push_back( streets[ streetId ] );
    } else if( route[ size - 1 ]->equals( streets[ streetId ] ) ){
        route.push_back( streets[ streetId ] );
    } else {
        exit( 16 );
    }

    this->posX = route[ 0 ]->GetStreetStart().GetX();
    this->posY = route[ 0 ]->GetStreetStart().GetY();
    this->current = route[ 0 ];
    this->currenti = 1;
}

void Bus::NameIt( QString streetName ){
    this->name = streetName;
}

void Bus::IdIt( QString ID ){
    this->id = ID;
}

QPointF Bus::GetPossition(){
    QPointF start;
    start.rx() =  route[ 0 ]->GetStreetStart().GetX() -2.5 ;
    start.ry() =  route[ 0 ]->GetStreetStart().GetY() -2.5 ;
    return start;
}

void Bus::setBus(){
    nextPos();
    this->onmap = true;
}

QPointF Bus::getPos(){
    QPointF x;
    x.rx() = this->posX - 2.5;
    x.ry() = this->posY - 2.5;
    return x;
}

void Bus::setNul(){
    atEnd = true;
    switcher = false;
    stationary = false;
    halflength = false;
    useRest = false;
    stopAtStop = false;
    currentStops = 0;
}

void Bus::countAdditions( float sx, float sy, float ex, float ey ){

    bool newStreet = false;

    float stepX = 0;
    float stepY = 0;

    float XDiff = abs( ex - sx );
    float YDiff = abs( ey - sy );
    hypotenuse = sqrt( pow( XDiff, 2 ) + pow( YDiff, 2 ) );

    if( stationary ){
        streetLength = 0;
        stationary = false;
    }

    if( halflength ){
        hypotenuse = hypotenuse / 2;
        XDiff = XDiff / 2;
        YDiff = YDiff / 2;
    }

    if( streetLength + step >= hypotenuse ){
        step = hypotenuse - streetLength;
        rest = step;
        newStreet = true;
    }

    if( useRest ){
        stepX = XDiff / ( hypotenuse / ( step + rest ) );
        stepY = YDiff / ( hypotenuse / ( step + rest ) );
        streetLength = streetLength + step + rest;
        useRest = false;
    } else {
        stepX = XDiff / ( hypotenuse / ( step ) );
        stepY = YDiff / ( hypotenuse / ( step ) );
        streetLength = streetLength + step;
    }

    if( ( ( streetLength > hypotenuse / 2 ) && ( streetLength - step < hypotenuse / 2 ) ) && ( current->getStop() ) && stopAtStop ){
        this->posX = current->GetMiddle()->GetX();
        this->posY = current->GetMiddle()->GetY();
        changeStop = true;
        stopAtStop = false;
        stationary = true;
        halflength = true;
        if( now == plannedStops.size() - 2 ){
            now = -1;
            departure = plannedStops[ 0 ][ 1 ];
            setNul();
        }
    } else if ( sx <= ex ){
        if( sy <= ey ){
            this->posX = this->posX + stepX;
            this->posY = this->posY + stepY;
        } else {
            this->posX = this->posX + stepX;
            this->posY = this->posY - stepY;
        }
    } else {
        if( sy < ey ){
            this->posX = this->posX - stepX;
            this->posY = this->posY + stepY;
        } else {
            this->posX = this->posX - stepX;
            this->posY = this->posY - stepY;
        }
    }

    if( newStreet && route.size() - 1 != currenti ){
        current = route[ currenti ];
        currenti++;
        stopAtStop = true;
        useRest = true;
        halflength = false;
        streetLength = 0;
    } else if ( newStreet && route.size() - 1 == currenti ){
        currenti = 1;
        current = route[ currenti - 1 ];
        stopAtStop = true;
        useRest = true;
        halflength = false;
        streetLength = 0;
        round = true;
    }

}

float Bus::countDistanceToStop(){
    float length = 0;
    for( int i = currenti - 1; i < route.size(); i++ ){
        length = length + countStreetLenght( route[ i ] );
        if( route[ i ]->getStop() ){
            if( plannedStops.size() <= ( now + 1 ) ){
                break;
            }
            if( route[ i ]->getStop()->getID() == plannedStops[ now + 1 ][ 0 ] ){
                break;
            }
        }
    }
    return length;
}

int Bus::timeToNext(){

    int firstStopMin = plannedStops[ now ][ 1 ].left( 2 ).toInt();
    int secondStopMin = plannedStops[ now + 1 ][ 1 ].left( 2 ).toInt();
    int firtStopSec = plannedStops[ now ][ 1 ].right( 2 ).toInt();
    int secondStopSec = plannedStops[ now + 1 ][ 1 ].right( 2 ).toInt();

    if( secondStopMin == 99 ){
        return 100;
    }

    int secondsToStop = ( secondStopMin - firstStopMin )*60 + ( secondStopSec - firtStopSec );

    return secondsToStop;
}

void Bus::nextPos(){

    if( changeStop ){
        now++;
    }

    if( currenti == 1 || changeStop ){
        length = countDistanceToStop();
        changeStop = false;
    }

    step = length / ( int ) length;

    int timeTo = timeToNext();

    departure = plannedStops[ now ][ 1 ];

    step = ( length * step ) / ( timeTo - 3 );

    if( currenti == 1 && !round ){
        countAdditions( current->GetMiddle()->GetX(), current->GetMiddle()->GetY(), current->GetStreetEnd().GetX(), current->GetStreetEnd().GetY() );
    } else if( currenti == 1 && round ){
        countAdditions( current->GetStreetStart().GetX(), current->GetStreetStart().GetY(), current->GetStreetEnd().GetX(), current->GetStreetEnd().GetY() );
    } else {
        if( current->GetStreetEnd().GetX() == route[ currenti - 2 ]->GetStreetEnd().GetX() && current->GetStreetEnd().GetY() == route[ currenti - 2 ]->GetStreetEnd().GetY() ){
            countAdditions( current->GetStreetEnd().GetX(), current->GetStreetEnd().GetY(), current->GetStreetStart().GetX(), current->GetStreetStart().GetY() );
        } else if ( current->GetStreetEnd().GetX() == route[ currenti - 2 ]->GetStreetStart().GetX() && current->GetStreetEnd().GetY() == route[ currenti - 2 ]->GetStreetStart().GetY() ){
            countAdditions( current->GetStreetEnd().GetX(), current->GetStreetEnd().GetY(), current->GetStreetStart().GetX(), current->GetStreetStart().GetY() );
        } else {
            countAdditions( current->GetStreetStart().GetX(), current->GetStreetStart().GetY(), current->GetStreetEnd().GetX(), current->GetStreetEnd().GetY() );
        }
    }

    if( current->getStop() ){
        qDebug() << "mam te pico";
        if( current->getStop()->getID() != plannedStops[ currentStops ][ 0 ] ){
            currentStops++;
        }
        qDebug() << "sem uz se nedostanu";
    }

}

QString Bus::getId(){
    return this->id;
}

QString Bus::getName(){
    return this->name;
}

QPointF Bus::getMiddle(){
    QPointF ret;
    ret.rx() = current->GetMiddle()->GetX() - 2.5;
    ret.ry() = current->GetMiddle()->GetY() - 2.5;
    this->posX = ret.rx() + 2.5;
    this->posY = ret.ry() + 2.5;
    return ret;
}

void Bus::setStart( QString time ){
    this->start = time;
}

QString Bus::getStart(){
    return this->start;
}

void Bus::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    qDebug() << startTime;
}

void Bus::getStops(){

    for( int i = 0; i < route.size(); i++ ){
        if( route[ i ]->getStop() ){
            stopsOnRoute.push_back( route[ i ]->getStop()->getID() );
        }
    }

    // -1 protoze zastavka na konci je stejna jako na zacatku kvuli dojeti na zastavku
    for( int i = currentStops; i < stopsOnRoute.size() - 1; i++ ){
        if( stopsOnRoute[ i ] != plannedStops[ i ][ 0 ] ){
            qDebug() << "Zastavky na ceste se neshoduji se zadanymi";
            quick_exit( 60 );
        }
    }

}

float Bus::countStreetLenght( Street *street ){
    float sx = street->GetStreetStart().GetX();
    float sy = street->GetStreetStart().GetY();
    float ex = street->GetStreetEnd().GetX();
    float ey = street->GetStreetEnd().GetY();

    float XDiff = abs( sx - ex );
    float YDiff = abs( sy - ey );

    if( street->getStop() ){
        return( sqrt( pow( XDiff, 2 ) + pow( YDiff, 2 ) ) / 2 );
    } else {
        return( sqrt( pow( XDiff, 2 ) + pow( YDiff, 2 ) ) );
    }
}
