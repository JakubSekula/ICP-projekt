#include "readcsv.h"

readcsv::readcsv( QString filecsv  ){

    QFile file( filecsv );
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in( &file );
        QString line = in.readLine();

        while ( !line.isNull() ) {
            line = in.readLine();
            QStringList row = line.split(',');
            if( row[ 0 ] == "" ){
                break;
            }

            c1 = new coordinate ( row[ 2 ].toInt(), row[ 3 ].toInt() );
            c2 = new coordinate ( row[ 4 ].toInt(), row[ 5 ].toInt() );

            street = new Street( row[ 0 ], row[ 1 ], *c1, *c2 );

            if( row[ 6 ] == "YES" ){
                s1 = new stop( row[ 0 ], row[ 1 ] );
                street->AddStop( s1 );
            }

            hash.insert( row[ 0 ], street );
        }

}

QMap<QString,Street*> readcsv::GetHash(){
    return this->hash;
}

QVector<QVector<int>> readcsv::GetArrayOfCords( QMap<QString,Street*> makearray ){

    QVector<QVector<int>> outer;

    int t = 0;

    QMap<QString, Street*>::iterator i;
    for ( i = makearray.begin(); i != makearray.end(); ++i ){
        QVector<int> inner;
        inner.push_back( makearray[ i.key() ]->GetStreetStart().GetX() );
        inner.push_back( makearray[ i.key() ]->GetStreetStart().GetY() );
        inner.push_back( makearray[ i.key() ]->GetStreetEnd().GetX() );
        inner.push_back( makearray[ i.key() ]->GetStreetEnd().GetY() );
        outer.push_back( inner );
        t += 1;
    }

    return outer;
}
