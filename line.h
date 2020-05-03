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
    void setId( QString identif );
    void setReps( QString repeats );
    void fillMap( QString id, QVector<QVector<QString>> stoptime );
    QVector<QVector<QString>> getStoptInfo( QString identif );
};

#endif // LINE_H
