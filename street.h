#ifndef STREET_H
#define STREET_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <QString>
#include "coordinate.h"
#include <QGraphicsLineItem>
#include "stop.h"

using namespace::std;

class Street : public QGraphicsLineItem{

private:
    QString name;
    QString id;
    vector<coordinate> coordinates;
    stop* s1 = NULL;
    coordinate* middle = NULL;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

public:

    /**
     * @brief Street::Street Konstruktor. Naastavenie cesty
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
     * @brief Street::equals Metoda pro zjisteni spravneho smeru jizdy.
     * @param street1
     * @param street2
     * @return Vrati true jestlize se ma cestovat doleva. jinak false
     */
    bool WhichWay( Street* street1, Street* street2 );

};


#endif // STREET_H
