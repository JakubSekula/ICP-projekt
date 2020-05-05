#ifndef LINE_H
#define LINE_H

#include <QString>
#include <QMap>
#include <QDebug>
#include <QVector>

class line
{

public:
    QString id;
    QString reps;
    QMap<QString,QVector<QVector<QString>>> stoptimes;
    QVector<QVector<QString>>stoptime;

public:
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
