/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file line.h
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief informace o lince
 */

#ifndef LINE_H
#define LINE_H

#include <QString>
#include <QMap>
#include <QDebug>
#include <QVector>

/**
 * @brief The line class Informace o lince
 */
class line
{

public:
    QString id;//!<id linky
    QString reps; //!< kolik busu se ma zobrazit v prubehu hodiny
    QMap<QString,QVector<QVector<QString>>> stoptimes; //!< doby zastavek
    QVector<QVector<QString>>stoptime; //!< cas zastaveni

public:
    /**
     * @brief Line Konstruktor
     */
    line();

    /**
     * @brief line::setId
     * @param identif ID spoja
     */
    void setId( QString identif );

    /**
     * @brief line::setReps
     * @param repeats Pocet opakovani
     */
    void setReps( QString repeats );

    /**
     * @brief line::fillMap
     * @param id ID autobusu
     * @param stoptime Cas odchodu mhd
     */
    void fillMap( QString id, QVector<QVector<QString>> stoptime );

    /**
     * @brief line::getStoptInfo
     * @param identif ID spoja
     * @return Vracia
     */
    QVector<QVector<QString>> getStoptInfo( QString identif );
};

#endif // LINE_H
