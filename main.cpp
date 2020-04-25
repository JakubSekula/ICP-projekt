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


    QMap<QString, Street*> phony;
    auto* map = new readcsv( "newyork.csv", "Map", phony );

    // ziskam map nacteny z csv souboru
    QMap<QString, Street*> streets = map->GetMapHash();

    auto* bus = new readcsv( "Bus.csv", "Bus", streets );

    QMap<QString, Bus*> busses = bus->GetBusHash();

    QApplication a(argc, argv);
    MainWindow w;
    w.initScene( streets, busses );
    w.show();
    return a.exec();
}
