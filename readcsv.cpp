#include "readcsv.h"

readcsv::readcsv( QString filecsv, QString FileType, QMap<QString, Street*> hashStreet, QMap<QString, line*> lines ){

        if( FileType == "Map" ){
            LoadMap( filecsv );
        } else if ( FileType == "Bus" ){
            LoadBus( filecsv, hashStreet, lines );
        } else if ( FileType == "Line" ){
            LoadLine( filecsv );
        }else {
            exit( 32 );
        }

}

QMap<QString,Street*> readcsv::GetMapHash(){
    return this->hash;
}

QMap<QString, QMap<QString, Bus*>> readcsv::GetBusHash(){
    return this->Busses;
}

QMap<QString, line*> readcsv::GetLineHash(){
    return this->lineHash;
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
            s1 = new stop();
            s1->initialize( row[ 0 ], row[ 1 ] );
            street->AddStop( s1 );
        }

        hash.insert( row[ 0 ], street );
    }

}

void readcsv::LoadBus( QString filecsv, QMap<QString, Street*> hashStreet, QMap<QString, line*> lines ){

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

        int iter = 0;
        while( iter < lines[ row[ 0 ] ]->reps.toInt() ){

            QVector<QString> times;
            QVector<QVector<QString>> test = lines[ row[ 0 ] ]->getStoptInfo( row[ 0 ] );
            times.push_back( getTimeDiff( test[ 0 ][ 1 ], lines[ row[ 0 ] ]->reps.toInt(), iter ) );

            getTimeDiff( test[ 0 ][ 1 ], lines[ row[ 0 ] ]->reps.toInt(), iter );

            if( times[ 0 ].size() == 1 ){
                times[ 0 ] = "0" + times[ 0 ] + " : " + test[ 0 ][ 1 ].right( 2 );
            }

            if( times[ 0 ].size() == 2 ){
                times[ 0 ] = times[ 0 ] + " : " + test[ 0 ][ 1 ].right( 2 );
            }

            bus = new Bus();
            bus->getStreets( hashStreet );
            bus->NameIt( row[ 0 ] );

            for( int i = 0; i < row.size(); i++ ){
                if( i >= 1 ){
                    bus->setRout( row[ i ] );
                }
            }

            int realstart;

            realstart = lines[ row[ 0 ] ]->reps.toInt() + lines[ row[ 0 ] ]->reps.toInt() * iter;

            QString real = QString::number(realstart);

            if( real.size() == 1 ){
                real = "0" + real;
            }

            bus->setStart( times[ 0 ] );

            busHash.insert( QString::number( iter ), bus );
            iter++;
        }
        this->Busses.insert( row[ 0 ], busHash );
        busHash.clear();
    }
}

void readcsv::LoadLine( QString filecsv ){
    QFile file( filecsv );
        if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
            return;

    QTextStream in( &file );

    QString lines = in.readLine();

    while ( !lines.isNull() ) {
        lines = in.readLine();
        QStringList row = lines.split(',');
        if( row[ 0 ] == "" ){
            break;
        }

        QMap<int,line*> instances;
            Line = new line();

            Line->setReps( row[ 1 ] );
            Line->setId( row[ 0 ] );
            QVector<QString> stoptime;
            QVector<QVector<QString>> entire;

            for( int i = 0; i < row.size(); i++ ){
                if( i >= 2 ){
                    QStringList separate = row[ i ].split('/');
                    stoptime.push_back( separate[ 0 ] );
                    stoptime.push_back( separate[ 1 ] );
                    entire.push_back( stoptime );
                    stoptime.clear();
                }
            }
            Line->fillMap( row[ 0 ], entire );
        lineHash.insert( row[ 0 ], Line );
    }
}

QString readcsv::getTimeDiff( QString time, int reps, int iter ){
    QString time1 = time.left( 2 );
    QString time2 = time.right( 2 );
    time = time1 + time2;
    int timeInt = time.toInt();
    timeInt = timeInt + timeInt * iter;
    time = QString::number( timeInt );
    if( time.size() == 2 ){
        float convert = time.toFloat() / 60;
          time = "0" + QString::number( convert ).left( 1 );
          QString zero;
          zero = QString::number( convert );
          if( zero.indexOf( "." ) != 1 ){
              zero = "0";
          } else {
              QStringList separate = zero.split('.');
              zero = "0." + separate[ 1 ];
          }
          convert = zero.toFloat() * 60;
          convert = ( int ) convert;
          QString add = QString::number( convert );
          if( add.size() == 1 ){
              add = "0" + add;
              time = time + " : " + add;
          } else {
              time = time + " : " + QString::number( convert ).left( 2 );
          }
    } else if ( time.size() == 3 ){
      float convert = time.toFloat() / 60;
        time = "0" + QString::number( convert ).left( 1 );
        QString zero;
        zero = QString::number( convert );
        if( zero.indexOf( "." ) != 1 ){
            zero = "0";
        } else {
            QStringList separate = zero.split('.');
            zero = "0." + separate[ 1 ];
        }
        convert = zero.toFloat() * 60;
        convert = ( int ) convert;
        QString add = QString::number( convert );
        if( add.size() == 1 ){
            add = "0" + add;
            time = time + " : " + add;
        } else {
            time = time + " : " + QString::number( convert ).left( 2 );
        }
    }
    return time;
}
