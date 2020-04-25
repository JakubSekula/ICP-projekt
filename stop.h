#ifndef STOP_H
#define STOP_H

#include <QString>

class stop
{

private:
    QString name;
    QString id;

public:
    stop( QString identif, QString name);
    QString getName();
};

#endif // STOP_H
