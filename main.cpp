/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file mainw.cpp
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief načítání informací do proměnných a volání grafiky
 */

#include "mainwindow.h"
#include <QtWidgets>
#include <QtDebug>
#include <QLabel>
#include <QTextStream>
#include <QString>
#include <QFile>
#include "coordinate.h"
#include "street.h"
#include "line.h"
#include "readcsv.h"
#include <QApplication>
#include <QVector>

int main(int argc, char *argv[])
{

    // konstruktor nacte csv do mapy

    QMap<QString, Street*> phony;
    QMap<QString, line*> phonyl;
    auto* map = new readcsv( "newyork.csv", "Map", phony, phonyl );

    // ziskam map nacteny z csv souboru
    QMap<QString, Street*> streets = map->GetMapHash();

    auto* lined = new readcsv( "link.csv", "Line", streets, phonyl );

    QMap<QString, line*> lines = lined->GetLineHash();

    auto* bus = new readcsv( "Bus.csv", "Bus", streets, lines );

    QMap<QString, QMap<QString, Bus*>> busses = bus->GetBusHash();

    QApplication a(argc, argv);
    MainWindow w;
    w.initScene( streets, busses, lines );
    w.show();
    return a.exec();
}

