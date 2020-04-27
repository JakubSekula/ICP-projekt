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
    QString time_str = time.toString( "hh : mm : ss" );
    ui->lineEdit->setText( time_str );
    timer->start( 1000 );
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

void MainWindow::initScene( QMap<QString, Street*> streets, QMap<QString, Bus*> bussesHash ){

    QPainter painter(this);
    QPen blue( Qt::blue, 4 );
    QPen red( Qt::red, 2 );

    auto *scene = new QGraphicsScene( ui->graphicsView );

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

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


    QMap<QString, Bus*>::iterator b;
    for( b = bussesHash.begin(); b != bussesHash.end(); b++ ){
        auto* test = bussesHash[ b.key() ];
        scene->addItem( test );
        test->setPos( test->GetPossition() );
        test->setBus();
        this->busses.push_back( test );
    }
    ui->graphicsView->setRenderHint( painter.Antialiasing );

}



void MainWindow::get_time(){
    BusMovement();
    QTime time = QTime::fromString( ui->lineEdit->text(),"hh : mm : ss" );
    time = time.addSecs(1);
    QString time_str = time.toString( "hh : mm : ss" );
    ui->lineEdit->setText( time_str );
}

void MainWindow::speed( int x ){
    timer->stop();
    timer->start( 1000/x );
}

void MainWindow::BusMovement(){

    for( int i = 0; i < busses.size(); i++ ){
        if( i != 0 ){
            auto* bus = busses[ i ];
            bus->setPos( busses[ i ]->getPos() );
            busses[ i ]->setBus();
        }
    }
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
