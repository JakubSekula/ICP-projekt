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

void MainWindow::resetBtnChecked(){

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
    QTime time = QTime::fromString( "12:00:00" );
    ui->lineEdit->setTime( time );
    ui->graphicsView->setTransform(org);
    ui->speeder->setValue(1);
    ui->graphicsView_2->setScene(new QGraphicsScene( ui->graphicsView_2 ));
}

void MainWindow::zoom( int x ){
    auto org = ui->graphicsView->transform();
    qreal scale = x / 10.0;
    ui->graphicsView->setTransform( QTransform( scale, org.m12(), org.m21(), scale, org.dx(), org.dy()));
}

/**
 * @brief MainWindow::initScene Vykreslenie mapy
 * @param streets
 * @param bussesHash
 * @param linkHash
 */
void MainWindow::initScene( QMap<QString, Street*> streets, QMap<QString, QMap<QString, Bus*>> bussesHash, QMap<QString, line*> linkHash ){

//    QPainter painter(this);

    this->bussesHash = bussesHash;
    this->linkHash = linkHash;

    QGraphicsScene* scene = new QGraphicsScene( ui->graphicsView );

    this->scene = scene;

    ui->graphicsView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );

    ui->graphicsView->setScene( scene );

    ui->graphicsView->scale( 1.2, 1.2 );

    QMap<QString, Street*>::iterator i;
    for ( i = streets.begin(); i != streets.end(); ++i ){

        //auto *line = scene->addLine( streets[ i.key() ]->GetStreetStart().GetX(), streets[ i.key() ]->GetStreetStart().GetY(), streets[ i.key() ]->GetStreetEnd().GetX(), streets[ i.key() ]->GetStreetEnd().GetY() );

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

/**
 * @brief MainWindow::spawnBus Pridanie autobusu do mapy na zaciatocnu zastavku
 */
void MainWindow::spawnBus(){

    QMap<QString, QMap<QString,Bus*>>::iterator test;
    for( test = bussesHash.begin(); test != bussesHash.end(); test++ ){
        for( auto* bus : *test ){
            QString sysTime = ui->lineEdit->text().right( 7 ).split( ' ', QString::SkipEmptyParts ).join( "" );
            QString myTime = bus->getStart();
            if( ( myTime == sysTime ) && ( bus->onmap == false ) ){
                connect( bus, SIGNAL( valueChangedd( QVector<QVector<QString>>, int, QVector<Street*>, bool ) ), this, SLOT( BusSignal( QVector<QVector<QString>>, int, QVector<Street*>, bool ) ) );
                bus->startTime = sysTime;
                scene->addItem( bus );
                bus->setPos( bus->getMiddle() );
                bus->setBus();
                bus->enRoute = true;
                this->busses.push_back( bus );
            }
        }
    }
}



void MainWindow::get_time(){
    QTime time = QTime::fromString( ui->lineEdit->text(), "hh : mm : ss" );
    spawnBus();
    jump = ( time.msecsTo(lastTime) / 1000 ) * -1;
    lastTime = time;
    BusMovement();
    time = time.addSecs( 1 );
    ui->lineEdit->setTime( time );
}

void MainWindow::speed( int x ){
    timer->stop();
    timer->start( 1000/x );
}

bool MainWindow::depart( Bus* bus ){
    QString times = ui->lineEdit->text().right( 7 );
    times = times.left( 2 ) + times.right( 2 );
    int timerTime = times.toInt();
    QString busDepart = bus->departure;
    if( bus->departure == "" ){
        busDepart = bus->start;
    } else {
        busDepart = bus->departure;
    }
    busDepart = busDepart.left( 2 ) + busDepart.right( 2 );
    int busDep = busDepart.toUInt();

    int busStart = ( bus->start.left( 2 ) + bus->start.right( 2 ) ).toInt();
    if( busStart == timerTime ){
    bus->enRoute = true;
    }
    if( bus->enRoute == false ){
    return false;
    }
    //qDebug() << timerTime << busDep;
    if( timerTime < busDep && bus->stationary ){
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

/**
 * @brief MainWindow::BusMovement Vykreslovanie autobusu, pohyb autobusu
 */
void MainWindow::BusMovement(){
    int o = 0;
    while( o < jump ){
        for( int i = 0; i < busses.size(); i++ ){
            if( i != 0 ){
                auto* bus = busses[ i ];
                 if( depart( bus ) && bus->enRoute ){
                    bus->setPos( busses[ i ]->getPos() );
                    busses[ i ]->setBus();
                }
            }
        }
        o++;
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
