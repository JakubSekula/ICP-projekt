#include "mainwindow.h"
#include <QtWidgets>
#include <QtDebug>
#include <QLabel>
#include <QTextStream>
#include <QString>
#include <QFile>
#include "coordinate.h"
#include "street.h"
#include "readcsv.h"
#include <QApplication>
#include <QVector>

int main(int argc, char *argv[])
{
    // konstruktor nacte csv do mapy
    readcsv csv( "newyork.csv" );

    // ziskam map nacteny z csv souboru
    QMap<QString, Street*> streets = csv.GetHash();

    // ziskam 2d vector souradnic
    QVector<QVector<int>> coordsvector = csv.GetArrayOfCords( streets );

    QApplication a(argc, argv);
    MainWindow w;
    w.initScene( streets );
    w.show();
    return a.exec();
}
