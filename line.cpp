/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file line.cpp
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief informace o lince
 */

#include "line.h"

line::line(){

}

//nastavenie id
void line::setId( QString identif ){
    this->id = identif;
}

//nastavenie opakovani
void line::setReps( QString repeats ){
    this->reps = repeats;
}

void line::fillMap( QString id, QVector<QVector<QString>> stoptime ){
    this->stoptimes.insert( id, stoptime );
}

QVector<QVector<QString>> line::getStoptInfo( QString identif ){
    return this->stoptimes[ identif ];
}
