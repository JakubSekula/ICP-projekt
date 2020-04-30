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
    void LoadMap( QString filecsv );
    void LoadBus( QString filecsv, QMap<QString, Street*> hashStreet, QMap<QString, line*> lines );
    void LoadLine( QString filecsv );
    QMap<QString, QMap<QString, Bus*>> Busses;

private:
    Bus* bus;
    coordinate* c1;
    coordinate* c2;
    stop* s1;
    line* Line;
    Street* street;
    QMap<QString, Street*> hash;
    QMap<QString, Bus*> busHash;
    QMap<QString, line*> lineHash;
    QString getTimeDiff( QString time, int reps, int iter );
};

#endif // READCSV_H
