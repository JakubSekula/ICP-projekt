#include "stop.h"

stop::stop( QString identif, QString name ){
    this->id = identif;
    this->name = name;
}

QString stop::getName(){
    return this->name;
}
