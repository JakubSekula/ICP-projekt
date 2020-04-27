#include "bus.h"

QRectF Bus::boundingRect() const
{
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
}

QPointF Bus::getPos(){
    QPointF x;
    x.rx() = this->posX - 2.5;
    x.ry() = this->posY - 2.5;
    return x;
}

void Bus::nextPos(){
    if( switcher == false ){
        if( round( this->posX ) == current->GetStreetEnd().GetX() && round( this->posY ) == current->GetStreetEnd().GetY() ){
            if( this->route.size() > this->currenti ){
                if( switcher == false ){
                    if( !( current->GetStreetEnd().GetX() == route[ currenti ]->GetStreetStart().GetX() ) ){
                        switcher = true;
                    } else {
                        switcher = false;
                    }
                } else {
                    if( !( current->GetStreetStart().GetX() == route[ currenti ]->GetStreetEnd().GetX() ) ){
                        switcher = true;
                    } else {
                        switcher = false;
                    }
                }
                this->current = route[ currenti ];
                this->currenti++;
                if( switcher == false ){
                    this->posX = current->GetStreetStart().GetX();
                    this->posY = current->GetStreetStart().GetY();
                } else {
                    this->posX = current->GetStreetEnd().GetX();
                    this->posY = current->GetStreetEnd().GetY();
                }
            } else {
                return;
            }
        }
    } else {
        if( round( this->posX ) == current->GetStreetStart().GetX() && round( this->posY ) == current->GetStreetStart().GetY() ){
            if( this->route.size() > this->currenti ){
                if( switcher == false ){
                    if( !( current->GetStreetEnd().GetX() == route[ currenti ]->GetStreetStart().GetX() ) ){
                        switcher = true;
                    } else {
                        switcher = false;
                    }
                } else {
                    if( !( current->GetStreetStart().GetX() == route[ currenti ]->GetStreetEnd().GetX() ) ){
                        switcher = false;
                    } else {
                        switcher = true;
                    }
                }
                this->current = route[ currenti ];
                this->currenti++;
                if( switcher == false ){
                    this->posX = current->GetStreetStart().GetX();
                    this->posY = current->GetStreetStart().GetY();
                } else {
                    this->posX = current->GetStreetEnd().GetX();
                    this->posY = current->GetStreetEnd().GetY();
                }
            } else {
                return;
            }
        }
    }

    float Xdiffer = abs( current->GetStreetStart().GetX() - current->GetStreetEnd().GetX() );
    float Ydiffer = abs( current->GetStreetStart().GetY() - current->GetStreetEnd().GetY() );
    float ratio;

    if( Xdiffer >= Ydiffer ){
        ratio = Xdiffer/Ydiffer;
    } else {
        ratio = Ydiffer/Xdiffer;
    }

    //qDebug() << Xdiffer;
    //qDebug() << Ydiffer;

    if( Xdiffer > Ydiffer ){
        if( current->GetStreetStart().GetX() <= current->GetStreetEnd().GetX() ){
            this->xStep = 1;
        } else {
            this->xStep = -1;
        }
        if( current->GetStreetStart().GetY() <= current->GetStreetEnd().GetY() ){
            this->yStep = 1/ratio;
        } else {
            this->yStep = -1/ratio;
        }
    } else {
        if( current->GetStreetStart().GetY() <= current->GetStreetEnd().GetY() ){
            this->yStep = 1;
        } else {
            this->yStep = -1;
        }
        if( current->GetStreetStart().GetX() <= current->GetStreetEnd().GetX() ){
            this->xStep = 1/ratio;
        } else {
            //qDebug() << (1/ratio);
            this->xStep = -1/ratio;
        }
    }
    if( switcher == false ){
        this->posX = this->posX + this->xStep;
        this->posY = this->posY + this->yStep;
    } else {
        this->posX = this->posX - this->xStep;
        this->posY = this->posY - this->yStep;
    }
}

QString Bus::getId(){
    return this->id;
}

QString Bus::getName(){
    return this->name;
}

void Bus::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Bus";
    //emit valueChanged(1);
}
