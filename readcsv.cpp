﻿/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file readcsv.cpp
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief načítání csv souborů
 */


#include "readcsv.h"

readcsv::readcsv( QString filecsv, QString FileType, QMap<QString, Street*> hashStreet, QMap<QString, line*> lines ){

        if( FileType == "Map" ){
            LoadMap( filecsv );
        } else if ( FileType == "Bus" ){
            LoadBus( filecsv, hashStreet, lines );
        } else if ( FileType == "Line" ){
            LoadLine( filecsv, hashStreet );
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
                    if( !hashStreet.contains( row[ i ] ) ){
                        exit( 56 );
                    }
                    bus->setRout( row[ i ] );
                }
            }

            for( int i = 0; i < lines[ row[ 0 ] ]->stoptime.size(); i++ ){
                QVector<QString> test;
                if( i < lines[ row[ 0 ] ]->stoptime.size() - 1 ){
                    test.push_back( lines[ row[ 0 ] ]->stoptime[ i ][ 0 ] );
                    test.push_back( getTimeDiff( lines[ row[ 0 ] ]->stoptime[ i ][ 1 ], lines[ row[ 0 ] ]->reps.toInt(), iter ) );
                } else {
                    test.push_back( lines[ row[ 0 ] ]->stoptime[ i ][ 0 ] );
                    test.push_back( lines[ row[ 0 ] ]->stoptime[ i ][ 1 ] );
                }
                bus->plannedStops.push_back( test );
                test.clear();
            }

            int realstart;

            realstart = lines[ row[ 0 ] ]->reps.toInt() + lines[ row[ 0 ] ]->reps.toInt() * iter;

            QString real = QString::number(realstart);

            if( real.size() == 1 ){
                real = "0" + real;
            }

            bus->setStart( times[ 0 ] );

            bus->getStops();
            busHash.insert( QString::number( iter ), bus );
            iter++;
        }
        this->Busses.insert( row[ 0 ], busHash );
        busHash.clear();
    }
}

void readcsv::LoadLine( QString filecsv, QMap<QString, Street*> hashStreet ){
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
                    if( separate.size() != 2 ){
                        exit( 56 );
                    }
                    stoptime.push_back( separate[ 0 ] );
                    if( !hashStreet.contains( separate[ 0 ] ) ){
                        exit( 56 );
                    }
                    stoptime.push_back( separate[ 1 ] );
                    Line->stoptime.push_back( stoptime );
                    entire.push_back( stoptime );
                    stoptime.clear();
                }
            }
            entire.push_back( entire[ 0 ] );
        stoptime.push_back( entire[ 0 ][ 0 ] );
        // signalizace dojezdu
        stoptime.push_back( "99:99" );
        Line->stoptime.push_back( stoptime );
        stoptime.clear();
        Line->fillMap( row[ 0 ], entire );
        lineHash.insert( row[ 0 ], Line );
    }
}

QString readcsv::getTimeDiff( QString time, int reps, int iter ){
    if( time.length() != 5 ){
        exit( 50 );
    }
    int minutes = time.left(2).toInt();
    int another_departure = ( int ) 60/reps;
    QString departure = QString::number( another_departure * iter + minutes ) + " : " + time.right( 2 );
    if( departure.size() == 6 ){
        departure = "0" + departure;
    }
    departure = departure.split( ' ', QString::SkipEmptyParts ).join( "" );
    if( departure.left( 2 ).toInt() >= 60 ){
        departure = QString::number( departure.left( 2 ).toInt() - 60 ) + ":" + time.right( 2 );
        if( departure.size() == 4 ){
            departure = "0" + departure;
        }
    }
    return departure;
}
