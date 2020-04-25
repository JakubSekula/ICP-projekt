#ifndef STREET_H
#define STREET_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <QString>
#include "coordinate.h"
#include "stop.h"

using namespace::std;

class Street{

private:
    QString name;
    QString id;
    vector<coordinate> coordinates;
    stop* s1 = NULL;
    coordinate* middle = NULL;

public:
    Street( QString id, QString name, coordinate c1, coordinate c2 );

    QString GetStreetID();

    QString GetStreetName();

    coordinate GetStreetStart();

    coordinate GetStreetEnd();

    void AddStop( stop* stop );

    stop* getStop();

    void CountMiddle( coordinate c1, coordinate c2 );

    coordinate* GetMiddle();

    bool equals( Street* street );

};


#endif // STREET_H
