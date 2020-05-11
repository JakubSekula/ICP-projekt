/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file coordinate.h
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief informace o koordinátech
 */

#ifndef COORDINATE_H
#define COORDINATE_H

/**
 * @brief The coordinate class Informace o koordinátech
 */
class coordinate
{
public:

    /**
     * @brief coordinate::coordinate Nastavenie suradnice
     * @param x Suradnica X
     * @param y Suradnica Y
     */
    coordinate( float x, float y );

    /**
     * @brief coordinate::GetX
     * @return Vrati suradnicu X
     */
    float GetX();

    /**
     * @brief coordinate::GetY
     * @return Vrati suradnicu Y
     */
    float GetY();

private:
    float x, y; //!< x a y suradnica bodu
};

#endif // COORDINATE_H
