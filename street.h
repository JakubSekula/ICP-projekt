/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file street.h
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief Informace o ulicích
 */

#ifndef STREET_H
#define STREET_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <QString>
#include "coordinate.h"
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include "stop.h"

using namespace::std;

/**
 * @brief The Street class Informace o ulicích
 */
class Street : public QObject, public QGraphicsLineItem{
    Q_OBJECT
private:

    QString name;
    QString id;
    vector<coordinate> coordinates;
    stop* s1 = NULL;
    coordinate* middle = NULL;
    /**
     * @brief mousePressEvent Metoda zavolana pri kliknuti na cestu.
     *        Stara sa o zafarbenie ciest a vytvara signal pre oznacovanie ciest na obchadzku.
     * @param event
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

public:
    int color;//!<farba cesty
    bool changeable = true;//!<ci je mozne menit farbu cesty
    int delay = 0;//!<meskanie premavky
    /**
     * @brief Street::Street Konstruktor. Nastavenie cesty
     * @param id
     * @param name
     * @param c1
     * @param c2
     */
    Street( QString id, QString name, coordinate c1, coordinate c2 );

    /**
     * @brief Street::GetStreetID
     * @return Vrati id cesty
     */
    QString GetStreetID();

    /**
     * @brief Street::GetStreetName
     * @return Vrati meno cesty
     */
    QString GetStreetName();

    /**
     * @brief Street::GetStreetStart
     * @return Vrati zaciatocny suradnicu cesty
     */
    coordinate GetStreetStart();

    /**
     * @brief Street::GetStreetEnd
     * @return Vrati koncovu suradnicu cesty
     */
    coordinate GetStreetEnd();

    /**
     * @brief Street::AddStop Prida zastavku na cestu
     * @param stop zastavka na pridanie
     */
    void AddStop( stop* stop );

    /**
     * @brief Street::getStop
     * @return Vrati pointer na zastavku
     */
    stop* getStop();

    /**
     * @brief Street::CountMiddle Vypocita stred cesty
     * @param c1 Zaciatocna suradnica
     * @param c2 Konecna suradnica
     */
    void CountMiddle( coordinate c1, coordinate c2 );

    /**
     * @brief Street::GetMiddle
     * @return Vrati stred cesty
     */
    coordinate* GetMiddle();

    /**
     * @brief Street::equals Metoda pre porovnanie ciest.
     * @param street
     * @return Vrati true ak sa cesty rovnaju. inak false
     */
    bool equals( Street* street );

    /**
     * @brief Street::WhichWay Metoda pro zjisteni spravneho smeru jizdy.
     * @param street1
     * @param street2
     * @return Vrati true jestlize se ma cestovat doleva. jinak false
     */
    bool WhichWay( Street* street1, Street* street2 );
signals:
    /**
     * @brief isBlack Signal pri oznacovani uzavratych tras a obchadzky
     * @param middle Stred cesty
     * @param s Cesta
     */
    void isBlack(coordinate* middle, Street* s);

    /**
     * @brief setBackColor Signal pri ruseni cesty pre obchadzku
     * @param s Cesta
     */
    void setBackColor(Street* s);
};


#endif // STREET_H
