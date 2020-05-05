#include "line.h"

line::line(){

}
/**
 * @brief line::setId
 * @param identif ID spoja
 */
void line::setId( QString identif ){
    this->id = identif;
}
/**
 * @brief line::setReps
 * @param repeats Pocet opakovani
 */
void line::setReps( QString repeats ){
    this->reps = repeats;
}

/**
 * @brief line::fillMap
 * @param id ID zastavky
 * @param stoptime Cas odchodu mhd
 */
void line::fillMap( QString id, QVector<QVector<QString>> stoptime ){
    this->stoptimes.insert( id, stoptime );
}

/**
 * @brief line::getStoptInfo
 * @param identif ID spoja
 * @return Vracia
 */
QVector<QVector<QString>> line::getStoptInfo( QString identif ){
    return this->stoptimes[ identif ];
}
