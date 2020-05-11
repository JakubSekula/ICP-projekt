/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file coordinate.cpp
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief informace o koordinátech
 */

#include "coordinate.h"

//Konstruktor, nastavenie suradnic
coordinate::coordinate( float x, float y ){
    this->x = x;
    this->y = y;
}

//Vratenie suradnice X
float coordinate::GetX(){
    return this->x;
}

//Vratenie suradnice Y
float coordinate::GetY(){
    return this->y;
}
