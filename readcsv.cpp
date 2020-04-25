#include "readcsv.h"

readcsv::readcsv( QString filecsv, QString FileType, QMap<QString, Street*> hashStreet ){

        if( FileType == "Map" ){
            LoadMap( filecsv );
        } else if ( FileType == "Bus" ){
            LoadBus( filecsv, hashStreet );
        } else {
            exit( 32 );
        }

}

QMap<QString,Street*> readcsv::GetMapHash(){
    return this->hash;
}

QMap<QString,Bus*> readcsv::GetBusHash(){
    return this->busHash;
}

void readcsv::LoadMap( QString filecsv ){

    QFile file( filecsv );
        if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
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

void readcsv::LoadBus( QString filecsv, QMap<QString, Street*> hashStreet ){

    QFile file( filecsv );
        if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
            return;

    QTextStream in( &file );

    QString line = in.readLine();

    while ( !line.isNull() ) {
        line = in.readLine();
        QStringList row = line.split(',');
        if( row[ 0 ] == "" ){
            break;
        }

        bus = new Bus();
        bus->getStreets( hashStreet );
        bus->NameIt( row[ 1 ] );

        for( int i = 0; i < row.size(); i++ ){
            if( i >= 2 ){
                bus->setRout( row[ i ] );
            }
        }

        busHash.insert( row[ 0 ], bus );
    }
}
