#ifndef READCSV_H
#define READCSV_H

#include <QMap>
#include <QFile>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "coordinate.h"
#include "street.h"
#include "stop.h"
#include "bus.h"
#include "line.h"
#include <array>
#include <QVector>
#include <QDebug>


class readcsv
{
public:
    readcsv( QString filecsv, QString FileType, QMap<QString, Street*> hashStreet, QMap<QString, line*> lines );
    QVector<QVector<int>> GetArrayOfCords( QMap<QString,Street*> makearray );
    QMap<QString,Street*> GetMapHash();
    QMap<QString, QMap<QString, Bus*>> GetBusHash();
    QMap<QString, line*> GetLineHash();
    QMap<QString, QMap<QString, Bus*>> Busses;
    QVector<QVector<QString>>stopTimes;

    /**
     * @brief readcsv::LoadMap precitanie .csv suboru a nacitanie hodnot
     * @param filecsv .csv subor na citanie
     */
    void LoadMap( QString filecsv );

    /**
     * @brief readcsv::LoadBus precitanie .csv suboru a nacitanie hodnot
     * @param filecsv .csv subor na citanie
     */
    void LoadBus( QString filecsv, QMap<QString, Street*> hashStreet, QMap<QString, line*> lines );

    /**
     * @brief readcsv::LoadLine precitanie .csv suboru a nacitanie hodnot
     * @param filecsv .csv subor na citanie
     */
    void LoadLine( QString filecsv );

private:
    Bus* bus;
    coordinate* c1;
    coordinate* c2;
    stop* s1;
    line* Line;
    Street* street;
    QMap<QString, Street*> hash; //!< Mapa
    QMap<QString, Bus*> busHash; //!< Autobusy
    QMap<QString, line*> lineHash; //!< Spoje

    /**
     * @brief readcsv::getTimeDiff Vypocitanie odchodu
     * @param time
     * @param reps
     * @param iter
     * @return Vrati odchod autobusu
     */
    QString getTimeDiff( QString time, int reps, int iter );
};

#endif // READCSV_H
