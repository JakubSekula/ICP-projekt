#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iterator>
#include <QWidget>
#include <QString>
#include <QMouseEvent>
#include <QPushButton>
#include <QGraphicsItem>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->verticalSlider, &QSlider::valueChanged, this, &MainWindow::zoom );

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

void MainWindow::initScene( QVector<QVector<int>> lines, int iter ){
    auto *scene = new QGraphicsScene( ui->graphicsView );

    ui->graphicsView->setScene( scene );

    ui->graphicsView->scale( 1.5,1.5 );

    int i = 0;

    while( i < iter ){
        auto *line = scene->addLine( lines[i][0], lines[i][1], lines[i][2], lines[i][3] );

        line->setFlag( QGraphicsItem::ItemIsSelectable );

        i += 1;
    }
    ui->graphicsView->setRenderHint( QPainter::Antialiasing );
}
