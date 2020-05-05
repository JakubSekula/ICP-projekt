#include "bus.h"

/**
 * @brief Bus::boundingRect Vytvori kruh, znacku autobusu
 * @return Vracia objekt, kruh
 */
QRectF Bus::boundingRect() const{
    return QRectF( 0, 0, 5, 5 );
}

/**
 * @brief Bus::paint Vykreslenie kruhu
 * @param painter
 * @param option
 * @param widget
 */
void Bus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush( Qt::red );
    QPen pen( brush, 3 );
    painter->setPen( pen );
    painter->drawEllipse( rec );
}

/**
 * @brief Bus::Bus Konstruktor, zavola funkciu getBus()
 */
Bus::Bus(){
    getBus();
}

/**
 * @brief Bus::getStreets Nastavi
 * @param str
 */
void Bus::getStreets( QMap<QString, Street*> str ){
    this->streets = str;
}

/**
 * @brief Bus::getBus
 * @return Vrati pointer na widget kruhu zanzornujuceho autobus
 */
QGraphicsEllipseItem *Bus::getBus(){
    return this->bus;
}

/**
 * @brief Bus::getRoute
 * @return  vracia odkaz na trasu
 */
QVector<Street *> Bus::getRoute(){
    return( route );
}

/**
 * @brief Bus::setRout nastavienie trasy
 * @param streetId ID ulice
 */
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

/**
 * @brief Bus::NameIt nastavenie mena
 * @param streetName
 */
void Bus::NameIt( QString streetName ){
    this->name = streetName;
}
/**
 * @brief Bus::IdIt nastavenie id
 * @param ID
 */
void Bus::IdIt( QString ID ){
    this->id = ID;
}

/**
 * @brief Bus::GetPossition Vrati poziciu zaciatocnej stanice autobusu
 * @return Vracia objekt typu QPointF
 */
QPointF Bus::GetPossition(){
    QPointF start;
    start.rx() =  route[ 0 ]->GetStreetStart().GetX() -2.5 ;
    start.ry() =  route[ 0 ]->GetStreetStart().GetY() -2.5 ;
    return start;
}

/**
 * @brief Bus::setBus Nastavi polohu autobusu na mape
 */
void Bus::setBus(){
    nextPos();
    this->onmap = true;
}

/**
 * @brief Bus::getPos Vrati aktualnu polohu autobusu
 * @return Vracia objekt typu QPointF
 */
QPointF Bus::getPos(){
    QPointF x;
    x.rx() = this->posX - 2.5;
    x.ry() = this->posY - 2.5;
    return x;
}

void Bus::setNul(){
    atEnd = false;
    switcher = false;
    stationary = false;
    halflength = false;
    useRest = false;
    stopAtStop = false;
    enRoute = false;
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
        } else {
                    departure = plannedStops[ now + 1 ][ 1 ];
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

/**
 * @brief Bus::countDistanceToStop
 * @return  vrati vzdialenost do zastavky/najblizsieho zastavenia
 */
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

/**
 * @brief Bus::timeToNext
 * @return Vrati cas do dalsieho pohybu autobusu
 */
int Bus::timeToNext(){

    int firstStopMin = plannedStops[ now ][ 1 ].left( 2 ).toInt();
    int secondStopMin = plannedStops[ now + 1 ][ 1 ].left( 2 ).toInt();
    int firtStopSec = plannedStops[ now ][ 1 ].right( 2 ).toInt();
    int secondStopSec = plannedStops[ now + 1 ][ 1 ].right( 2 ).toInt();

    if( secondStopMin == 99 ){
        return 100;
    }

    int secondsToStop = ( secondStopMin - firstStopMin )*60 + ( secondStopSec - firtStopSec );

    // TODO osetreni stejnych minnut ale mensich sekund u druheho
    if( secondStopMin < firstStopMin ){
        secondsToStop =  3600 - firtStopSec - firstStopMin * 60;
        secondsToStop = secondsToStop + secondStopMin * 60 + secondStopSec;
    }



    return secondsToStop;
}

/**
 * @brief Bus::nextPos Zisti nasledujucu polohu autobusu
 */
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

    step = ( length * step ) / ( timeTo - 3 );

    departure = plannedStops[ now ][ 1 ];

    //qDebug() << step;

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
        if( current->getStop()->getID() != plannedStops[ currentStops ][ 0 ] ){
            currentStops++;
        }
    }

}

/**
 * @brief Bus::getId Vrati ID
 * @return
 */
QString Bus::getId(){
    return this->id;
}

/**
 * @brief Bus::getName Vrati meno
 * @return
 */
QString Bus::getName(){
    return this->name;
}

/**
 * @brief Bus::getMiddle Vrati stred
 * @return Vrati objekt typu QPointF
 */
QPointF Bus::getMiddle(){
    QPointF ret;
    ret.rx() = current->GetMiddle()->GetX() - 2.5;
    ret.ry() = current->GetMiddle()->GetY() - 2.5;
    this->posX = ret.rx() + 2.5;
    this->posY = ret.ry() + 2.5;
    return ret;
}

/**
 * @brief Bus::setStart Nastavi cas vyjazdu
 * @param time Cas zaciatku
 */
void Bus::setStart( QString time ){
    this->start = time;
}

/**
 * @brief Bus::getStart
 * @return Vrati cas vyjazdu
 */
QString Bus::getStart(){
    return this->start;
}

/**
 * @brief Bus::mousePressEvent
 * @param event
 */
void Bus::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    emit valueChangedd( plannedStops );
}

/**
 * @brief Bus::getStops
 */
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

/**
 * @brief Bus::countStreetLenght Vypocita a vrati dlzku cesty
 * @param street Pointer na objekt cesty
 * @return Vrati dlzku cesty
 */
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
