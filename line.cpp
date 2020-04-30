#include "line.h"

line::line(){

}

void line::setId( QString identif ){
    this->id = identif;
}

void line::setReps( QString repeats ){
    this->reps = repeats;
}


void line::fillMap( QString id, QVector<QVector<QString>> stoptime ){
    this->stoptimes.insert( id, stoptime );
}

QVector<QVector<QString>> line::getStoptInfo( QString identif ){
    return this->stoptimes[ identif ];
}
