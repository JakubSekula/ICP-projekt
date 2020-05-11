/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file mainwindow.cpp
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief hlavní grafické zobrazení
 */

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->verticalSlider, &QSlider::valueChanged, this, &MainWindow::zoom );
    connect( ui->speeder, SIGNAL( valueChanged( int ) ), this, SLOT( speed( int ) ) );

    timer = new QTimer( this );
    QTime time = QTime::fromString( "12:00:00" );
    ui->lineEdit->setDisplayFormat( "hh : mm : ss" );
    ui->lineEdit->setTime( time );
    timer->start( 1000 );
    lastTime = time;
    connect( timer, SIGNAL( timeout() ), this, SLOT( get_time() ) );
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetBtnChecked()));
    connect(ui->linkButton, SIGNAL(clicked()), this, SLOT(linkBtnChecked()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    clearPicked();
    ui->graphicsView_2->setScene(new QGraphicsScene( ui->graphicsView_2 ));
}

//tlacidlo reset
void MainWindow::resetBtnChecked(){

    actuallLink.clear();
    actuallStops.clear();
    //reset mapy
    QMap<QString, Street*> phony;
    QMap<QString, line*> phonyl;
    auto org = ui->graphicsView->transform();
    auto* map = new readcsv( "newyork.csv", "Map", phony, phonyl );
    QMap<QString, Street*> streets = map->GetMapHash();
    auto* lined = new readcsv( "link.csv", "Line", streets, phonyl );
    QMap<QString, line*> lines = lined->GetLineHash();
    auto* bus = new readcsv( "Bus.csv", "Bus", streets, lines );
    QMap<QString, QMap<QString, Bus*>> busses = bus->GetBusHash();
    initScene( streets, busses, lines );
    //reset casu
    QTime time = QTime::fromString( "12:00:00" );
    ui->lineEdit->setTime( time );
    //reset priblizenia
    ui->graphicsView->setTransform(org);
    //reset zrychlenia
    ui->speeder->setValue(1);
    //vycistenie spodnej casti
    ui->graphicsView_2->setScene(new QGraphicsScene( ui->graphicsView_2 ));
    ui->verticalSlider->setValue(15);
    //reset tlacidla na nastavenie obchadzky
    ui->linkButton->setText("Zmena trasy");
    changingLink = false;
    alternateRoute.clear();
}

void MainWindow::replaceRoute(){
    int i = 0;
    bool changeCurrenti = false;
    bool changeStreets = false;
    QMessageBox msgBox;
    int dly = 0;

    if( alternateRoute.size() == 1 ){
        msgBox.critical( 0, "Error", "Zvolte prosim objezdnou trasu" );
        deleteMarked();
        return;
    }

    QVector<Street*> newRoute;
    QVector<QVector<QString>> newStreets;

    for( Bus* bus : busses ){
        changeStreets = false;
        changeCurrenti = false;
        if( i != 0 ){
            QVector<Street*> streets = bus->getRoute();
            int str = 0;
            for( Street* street : streets ){
                if( street->GetStreetID() == alternateRoute.first()->GetStreetID() ){
                    if( !streets[ str ]->equals( alternateRoute.back() ) ){
                        msgBox.critical( 0, "Error", "Objizdka nenavazuje" );
                        deleteMarked();
                        return;
                    }
                    bus->clearRoute();
                    if( str < bus->currenti ){
                        changeCurrenti = true;
                    }
                    for( int i = 0; i < bus->plannedStops.size(); i++ ){
                        if( bus->plannedStops[ i ][ 0 ] == street->GetStreetID() ){
                            if( bus->now >= i ){
                                bus->switchNow = true;
                            } else if ( bus->now == i -1 ){
                                changeStreets = true;
                            } else {
                                bus->switchNow = false;
                            }
                        } else {
                            newStreets.push_back( bus->plannedStops[ i ] );
                        }
                    }
                    if( changeStreets == false ){
                        bus->setNewStreeets( newStreets );
                        bus->switchStop = true;
                        actuallStops.insert( bus->getName(), newStreets );
                        newStreets.clear();
                    }
                    int replacement = 0;
                    for( Street* streetReplace : alternateRoute ){
                        if( replacement != 0 ){

                            bus->delay = bus->delay + 5;
                            dly += 5;
                            newRoute.push_back( streetReplace );
                        }
                        replacement++;
                    }
                    delay.insert( bus->getName(), dly );
                    dly = 0;
                } else {
                    newRoute.push_back( street );
                }
                str++;
            }
                if( changeCurrenti ){
                    bus->currenti = bus->currenti + alternateRoute.size() - 2;
                }
                if( changeStreets ){
                    bus->plannedStops.clear();
                    bus->plannedStops = newStreets;
                    bus->refactor = true;
                    changeStreets = false;
                }
                bus->refactor = true;
                bus->refactorRoute = true;
                bus->clearRoute();
                bus->route = newRoute;
            actuallLink.insert( bus->getName(), newRoute );
            newRoute.clear();
        }
        i++;
    }
}

void MainWindow::deleteMarked(){
    //zmazanie obchadzky
    if( alternateRoute.size() != 0 ){
        for( Street* s : alternateRoute ){
            //zmena farby cesty na povodnu
           if(s->color == 1) s->setPen(QPen(QColor(99, 214, 104), 1.5));
           else if(s->color == 2) s->setPen(QPen(QColor(255, 151, 77), 1.5));
           else if(s->color == 3) s->setPen(QPen(QColor(242, 60, 50), 1.5));
        }
    }
    alternateRoute.clear();

    if( detour.size() != 0 ){
        delete detour[ detour.size() - 2 ];
        delete detour[ detour.size() - 1 ];
    }
    detour.clear();
}

QVector<QVector<QString>> MainWindow::getActualStops( Bus* bus ){
    QVector<QVector<QString>> stops = bus->plannedStops;

    int size = actuallStops[ bus->getName() ].size();
    int stopSize = stops.size();

    for( int i = 0; i < stopSize; i++ ){
        if( i < size ){
            if( stops[ i ][ 0 ] != actuallStops[ bus->getName() ][ i ][ 0 ] ){
                stops.remove( i );
                stopSize--;
            }
        }
    }
    bus->plannedStops.clear();
    return stops;
}

void MainWindow::alternateRouteFunc(){

        if( alternateRoute.size() == 0 ){
            return;
        }

        int i = 0;
        Street* current;
        for( Street* street : alternateRoute ){

            if( i != 0 ){
                if( current->equals( street ) ){

                } else {
                    QMessageBox msgBox;
                    msgBox.critical( 0, "Error", "Ulice na sebe nenavazuji" );
                    deleteMarked();
                    return;
                }
            }
            current = street;
            i++;
        }

        replaceRoute();

        alternateRoute.clear();
}

void MainWindow::linkBtnChecked(){
    if(changingLink){
        changingLink = false;
        ui->linkButton->setText("Zmena trasy");
        alternateRouteFunc();
    }
    else{
        changingLink = true;
        ui->linkButton->setText("Hotovo");
    }
}

void MainWindow::zoom( int x ){
    auto org = ui->graphicsView->transform();
    qreal scale = x / 10.0;
    ui->graphicsView->setTransform( QTransform( scale, org.m12(), org.m21(), scale, org.dx(), org.dy()));
}

void MainWindow::drawCross(coordinate* middle, Street* s){
    if(changingLink){
        if(alternateRoute.size() == 0){
            s->setPen(QPen(QColor(180,180,180), 1.5));

            QGraphicsLineItem* cross1 = scene->addLine(middle->GetX()-2,middle->GetY()-2,middle->GetX()+2,middle->GetY()+2, QPen(Qt::red, 1));
            QGraphicsLineItem* cross2 = scene->addLine(middle->GetX()-2,middle->GetY()+2,middle->GetX()+2,middle->GetY()-2, QPen(Qt::red, 1));
            detour.push_back( cross1 );
            detour.push_back( cross2 );
        }
        else{
            s->setPen(QPen(QColor(0,170,240), 1.5));
        }

        if(changingLink){
            alternateRoute.push_back(s);
        }
    }
}

//nastavenie farby cesty spat na povodnu
void MainWindow::backColor(Street* s){

    QVector<Street*>::iterator i;
    for ( i = alternateRoute.begin(); i != alternateRoute.end(); ++i ){
        if((*i)->GetStreetID() == s->GetStreetID()){
                i = alternateRoute.erase(i);

                if(s->color == 1) s->setPen(QPen(QColor(99, 214, 104), 1.5));
                else if(s->color == 2) s->setPen(QPen(QColor(255, 151, 77), 1.5));
                else if(s->color == 3) s->setPen(QPen(QColor(242, 60, 50), 1.5));

                if(i == alternateRoute.end()) break;
        }
    }
}

void MainWindow::initScene( QMap<QString, Street*> streets, QMap<QString, QMap<QString, Bus*>> bussesHash, QMap<QString, line*> linkHash ){

    this->bussesHash = bussesHash;
    this->linkHash = linkHash;

    QGraphicsScene* scene = new QGraphicsScene( ui->graphicsView );

    this->scene = scene;

    ui->graphicsView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );

    ui->graphicsView->setScene( scene );

    ui->graphicsView->scale( 1.2, 1.2 );

    QMap<QString, Street*>::iterator i;
    for ( i = streets.begin(); i != streets.end(); ++i ){
        connect(streets[ i.key() ], SIGNAL(isBlack(coordinate*, Street*)), this, SLOT(drawCross(coordinate*, Street*)));
        connect(streets[ i.key() ], SIGNAL(setBackColor(Street*)), this, SLOT(backColor(Street*)));
        scene->addItem( streets[ i.key() ] );

        stop* s1 = streets[ i.key() ]->getStop();

        if( s1 != NULL ){

            auto* stop = streets[ i.key() ]->getStop();

            scene->addItem( stop );

            stop->setPos( streets[ i.key() ]->GetMiddle()->GetX() - 2.5, streets[ i.key() ]->GetMiddle()->GetY() - 2.5 );

        }

    }

    ui->graphicsView->setRenderHint( QPainter::Antialiasing );

}

void MainWindow::spawnBus(){

    QMap<QString, QMap<QString,Bus*>>::iterator outer;
    for( outer = bussesHash.begin(); outer != bussesHash.end(); outer++ ){
        for( auto* bus : *outer ){
            QString sysTime = ui->lineEdit->text().right( 7 ).split( ' ', QString::SkipEmptyParts ).join( "" );
            QString myTime = bus->getStart();
            if( ( myTime == sysTime ) && ( bus->onmap == false ) ){
                connect( bus, SIGNAL( valueChangedd( QVector<QVector<QString>>, int, QVector<Street*>, bool ) ), this, SLOT( BusSignal( QVector<QVector<QString>>, int, QVector<Street*>, bool ) ) );
                bus->startTime = sysTime;
                scene->addItem( bus );
                bus->setPos( bus->getMiddle() );
                bus->setBus();
                bus->enRoute = true;
                if( actuallLink[ bus->getName() ].size() != 0 ){
                    bus->delay = delay[ bus->getName() ];
                    bus->clearRoute();
                    bus->route = actuallLink[ bus->getName() ];
                    if( actuallStops[ bus->getName() ].size() != 0 ){
                        bus->plannedStops = getActualStops( bus );
                    }
                }
                this->busses.push_back( bus );
            }
        }
    }
}

void MainWindow::get_time(){
    QTime time = QTime::fromString( ui->lineEdit->text(), "hh : mm : ss" );
    spawnBus();
    time = time.addSecs( 1 );
    if( ui->lineEdit->text().right( 7 ) == "00 : 00" ){
        timerTime = 0;
    }
    timerTime++;
    ui->lineEdit->setTime( time );
    lastTime = time;
    BusMovement();
}

void MainWindow::speed( int x ){
    timer->stop();
    timer->start( 1000/x );
}

int MainWindow::convertToSec( int BusDep, int delay ){

    if( BusDep < 10 ){
        return BusDep + delay;
    }

    int sec = ( QString::number( BusDep ).right( 2 ) ).toInt();
    int minutes = ( QString::number( BusDep ).left( QString::number( BusDep ).size() - 2 ) ).toInt();

    minutes = ( minutes * 60 ) + sec;
    delay = minutes + delay;

    return delay;
}

int MainWindow::convertToSec( int busDep ){

    if( busDep < 10 ){
        return busDep;
    }

    int sec = ( QString::number( busDep ).right( 2 ) ).toInt();
    int minutes = ( QString::number( busDep ).left( QString::number( busDep ).size() - 2 ) ).toInt();

    minutes = ( minutes * 60 ) + sec;
    return minutes;
}

bool MainWindow::depart( Bus* bus ){
    QString times = ui->lineEdit->text().right( 7 );
    times = times.left( 2 ) + times.right( 2 );
    QString busDepart = bus->departure;
    if( bus->departure == "" ){
        busDepart = bus->start;
    } else {
        busDepart = bus->departure;
    }
    busDepart = busDepart.left( 2 ) + busDepart.right( 2 );
    int busDep = busDepart.toUInt();

    int busStart = ( bus->start.left( 2 ) + bus->start.right( 2 ) ).toInt();

    if( convertToSec( busStart ) == timerTime ){
        bus->enRoute = true;
    }
    if( bus->enRoute == false ){
        return false;
    }

    if( timerTime < convertToSec( busDep, bus->delay ) && bus->stationary ){
        return false;
    } else {
        if( bus->atEnd == false ){
            return true;
        } else {
            return false;
        }
    }
}

void MainWindow::clearPicked(){
    for( int i = 0; i < pickedLines.size(); i++ ){
        delete pickedLines[ i ];
    }

    pickedLines.clear();
}

void MainWindow::BusMovement(){
    for( int i = 0; i < busses.size(); i++ ){
        if( i != 0 ){
            auto* bus = busses[ i ];
            if( depart( bus ) && bus->enRoute ){
                bus->setPos( busses[ i ]->getPos() );
                busses[ i ]->setBus();
            }
        }
    }
}

void MainWindow::BusSignal( QVector<QVector<QString>> stops, int currTime, QVector<Street*> route, bool inStation ){

    clearPicked();

    QGraphicsScene* scene2 = new QGraphicsScene( ui->graphicsView_2 );
    ui->graphicsView_2->setScene( scene2 );

    int x = 0;

    for( int i = 0; i < route.size(); i++  ){
        QGraphicsLineItem* line = scene->addLine( route[ i ]->GetStreetStart().GetX(), route[ i ]->GetStreetStart().GetY(), route[ i ]->GetStreetEnd().GetX(), route[ i ]->GetStreetEnd().GetY(), QPen( Qt::blue, 3 ) );
        pickedLines.push_back( line );
    }

    for( int i = 0; i < stops.size() - 1; i++ ){
        scene2->addEllipse( x , 0 - 2.5, 5, 5, QPen( Qt::blue, 5 ) );

        QGraphicsTextItem* textDepTime = scene2->addText( stops[ i ][ 1 ] );
        textDepTime->setTextWidth( 70 );
        textDepTime->setPos( x - 20, - 30 );

        QGraphicsTextItem* textStreetId = scene2->addText( stops[ i ][ 0 ] );
        textStreetId->setTextWidth( 70 );
        textStreetId->setPos( x - 20, 10 );

        x = x + 70;
    }

    x = 0;

    for( int i = 0; i < stops.size() - 1; i++ ){
        if( i < stops.size() - 2 ){
            scene2->addLine( x, 0, x + 70, 0, QPen( Qt::black, 1 ) );
        }

        if( currTime == - 1 ){
            scene2->addEllipse( 0, 0 - 2.5, 5, 5, QPen( Qt::red, 5 ) );
        }

        if( currTime == i && i < stops.size() - 2 && inStation == false ){
            scene2->addEllipse( x + 35 , 0 - 2.5, 5, 5, QPen( Qt::red, 5 ) );
        } else if ( currTime == i && i < stops.size() - 2 && inStation ){
            scene2->addEllipse( x + 70, 0 - 2.5, 5, 5, QPen( Qt::red, 5 ) );
        } else if ( i == stops.size() - 2 && currTime == i ){
            QGraphicsTextItem* busEnd = scene2->addText( "bus heading to end station" );
            busEnd->setDefaultTextColor( Qt::red );
            busEnd->setPos( x + 35, -10 );
        }

        x = x + 70;
    }


}
