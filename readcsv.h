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
#include <array>
#include <QVector>
#include <QDebug>


class readcsv
{
public:
    readcsv( QString filecsv, QString FileType  );
    QVector<QVector<int>> GetArrayOfCords( QMap<QString,Street*> makearray );
    QMap<QString,Street*> GetHash();
    void LoadMap( QString filecsv );
    void LoadBus( QString filecsv );

private:
    coordinate* c1;
    coordinate* c2;
    stop* s1;
    Street* street;
    QMap<QString, Street*> hash;
};

#endif // READCSV_H
