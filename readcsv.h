#ifndef READCSV_H
#define READCSV_H

#include <QMap>
#include <QFile>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "coordinate.h"
#include "street.h"
#include <array>
#include <QVector>


class readcsv
{
public:
    readcsv( QString filecsv  );
    QVector<QVector<int>> GetArrayOfCords( QMap<QString,Street*> makearray );
    QMap<QString,Street*> GetHash();

private:
    coordinate* c1;
    coordinate* c2;
    Street* street;
    QMap<QString, Street*> hash;
};

#endif // READCSV_H
