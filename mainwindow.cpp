#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iterator>
#include <QWidget>
#include <QString>
#include <QMouseEvent>
#include <QPushButton>
#include <QGridLayout>
#include <QDateTime>
#include <QVariantAnimation>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->verticalSlider, &QSlider::valueChanged, this, &MainWindow::zoom );
    connect( ui->speeder, SIGNAL( valueChanged( int ) ), this, SLOT( speed( int ) ) );

    timer = new QTimer(this);
    QTime time = QTime::currentTime();
    QString time_str = time.toString("hh : mm : ss");
    ui->Timer->setText(time_str);
    timer->start(1000);
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

void MainWindow::initScene( QMap<QString, Street*> streets ){

    QPainter painter(this);
    QPen blue( Qt::blue, 4 );
    QPen red( Qt::red, 2 );

    auto *scene = new QGraphicsScene( ui->graphicsView );
    ui->graphicsView->setScene( scene );

    ui->graphicsView->scale( 1.5,1.5 );

    QMap<QString, Street*>::iterator i;
    for ( i = streets.begin(); i != streets.end(); ++i ){

        auto *line = scene->addLine( streets[ i.key() ]->GetStreetStart().GetX(), streets[ i.key() ]->GetStreetStart().GetY(), streets[ i.key() ]->GetStreetEnd().GetX(), streets[ i.key() ]->GetStreetEnd().GetY() );

        line->setFlag( QGraphicsItem::ItemIsSelectable );

        stop* s1 = streets[ i.key() ]->getStop();

        if( s1 != NULL ){

            test = QRectF( streets[ i.key() ]->GetMiddle()->GetX() - 2.5, streets[ i.key() ]->GetMiddle()->GetY() -2.5, 5, 5 );

            auto* stopBus = scene->addEllipse( test, blue  );

        }

    }

    testik = new class Bus();

    testik->getStreets( streets );

    testik->setRout( "Pearl1" );
    testik->setRout( "Pearl2" );

    QVector<Street*> streetT = testik->getRoute();

    for ( int iter = 0; iter != streetT.size(); iter++ ){
        qDebug() << streetT[ iter ]->GetStreetName();
    }

    nesttt = testik->getBus();

    nesttt = scene->addEllipse( 0, 0, 5, 5, red );
    nesttt->setPos( testik->SetPossition() );

    busT = scene->addEllipse( 0, 0, 5, 5, red );
    busT->setPos( posX-2.5, posY-2.5 );

    ui->graphicsView->setRenderHint( QPainter::Antialiasing );
}

void MainWindow::get_time(){
    BusMovement();
    QTime time = QTime::fromString(ui->Timer->text(),"hh : mm : ss");
    time = time.addSecs(1);
    QString time_str = time.toString("hh : mm : ss");
    ui->Timer->setText(time_str);
}

void MainWindow::speed( int x ){
    timer->stop();
    timer->start( 1000/x );
}

void MainWindow::BusMovement(){



    std::vector<float>pos = CountInc();
    //qDebug() << pos[ 0 ];
    //qDebug() << pos[ 1 ];
    posX = posX + pos[ 0 ];
    posY = posY + pos[ 1 ];
    busT->setPos( posX-2.5, posY-2.5 );

}

std::vector <float> MainWindow::CountInc(){
    float Xdiffer = abs( 504 - posEX );
    float Ydiffer = abs( 217 - posEY );

    std::vector<float> result;

    if( Xdiffer > Ydiffer ){
        if( posEX < posX ){
            result.push_back( -1 );
        } else {
            result.push_back( 1 );
        }
        float Odifference = ( Xdiffer/Ydiffer );
        result.push_back( 1/Odifference );
        return( result );
    } else {
        float Odifference = ( Xdiffer/Ydiffer );
        result.push_back( 1/Odifference );
        result.push_back( 1 );
        return( result );
    }

}
