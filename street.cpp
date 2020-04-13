#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <QString>
#include "coordinate.h"

using namespace::std;

class Street{

    QString name;
    QString id;
    vector<coordinate> coordinates;

    public:
        Street( QString id, QString name, coordinate c1, coordinate c2 ){
            this->name = name;
            this->id = id;
            coordinates.push_back( c1 );
            coordinates.push_back( c2 );
        }

        QString GetStreetID(){
            return name;
        }

        QString GetStreetName(){
            return name;
        }

        coordinate GetStreetStart(){
            return( coordinates.front() );
        }

        coordinate GetStreetEnd(){
            return( coordinates.back() );
        }
};
