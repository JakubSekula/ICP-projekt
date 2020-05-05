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

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::zoom( int x ){
    auto org = ui->graphicsView->transform();
    qreal scale = x / 10.0;
    ui->graphicsView->setTransform( QTransform( scale, org.m12(), org.m21(), scale, org.dx(), org.dy()));
}

void MainWindow::initScene( QMap<QString, Street*> streets, QMap<QString, QMap<QString, Bus*>> bussesHash, QMap<QString, line*> linkHash ){

    QPainter painter(this);

    this->bussesHash = bussesHash;
    this->linkHash = linkHash;

    QGraphicsScene* scene = new QGraphicsScene( ui->graphicsView );

    this->scene = scene;

    ui->graphicsView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );

    ui->graphicsView->setScene( scene );

    ui->graphicsView->scale( 1.4, 1.4 );

    QMap<QString, Street*>::iterator i;
    for ( i = streets.begin(); i != streets.end(); ++i ){

        auto *line = scene->addLine( streets[ i.key() ]->GetStreetStart().GetX(), streets[ i.key() ]->GetStreetStart().GetY(), streets[ i.key() ]->GetStreetEnd().GetX(), streets[ i.key() ]->GetStreetEnd().GetY() );

        line->setFlag( QGraphicsItem::ItemIsSelectable );

        stop* s1 = streets[ i.key() ]->getStop();

        if( s1 != NULL ){

            auto* stop = streets[ i.key() ]->getStop();

            scene->addItem( stop );

            stop->setPos( streets[ i.key() ]->GetMiddle()->GetX() - 2.5, streets[ i.key() ]->GetMiddle()->GetY() - 2.5 );

        }

    }

    ui->graphicsView->setRenderHint( painter.Antialiasing );

}

void MainWindow::spawnBus(){

    QMap<QString, QMap<QString,Bus*>>::iterator test;
    for( test = bussesHash.begin(); test != bussesHash.end(); test++ ){
        for( auto* bus : *test ){
            QString sysTime = ui->lineEdit->text().right( 7 ).split( ' ', QString::SkipEmptyParts ).join( "" );
            QString myTime = bus->getStart();
            if( ( myTime == sysTime ) && ( bus->onmap == false ) ){
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
