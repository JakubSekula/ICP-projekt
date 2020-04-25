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
#include <array>
#include <QVector>
#include <QDebug>


class readcsv
{
public:
    readcsv( QString filecsv, QString FileType, QMap<QString, Street*> hashStreet );
    QVector<QVector<int>> GetArrayOfCords( QMap<QString,Street*> makearray );
    QMap<QString,Street*> GetMapHash();
    QMap<QString,Bus*> GetBusHash();
    void LoadMap( QString filecsv );
    void LoadBus( QString filecsv, QMap<QString, Street*> hashStreet );

private:
    Bus* bus;
    coordinate* c1;
    coordinate* c2;
    stop* s1;
    Street* street;
    QMap<QString, Street*> hash;
    QMap<QString, Bus*> busHash;
};

#endif // READCSV_H
