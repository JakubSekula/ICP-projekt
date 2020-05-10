/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file bus.h
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief informace o autobusech
 */


#ifndef BUS_H
#define BUS_H

#include <QDebug>
#include <QMap>
#include <QObject>
#include <QGraphicsEllipseItem>
#include "street.h"
#include <cmath>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QMessageBox>
#include <QObject>

class Bus : public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    /**
     * @brief Bus::switchStops zmeni zastavku
     */
    void switchStops();
    QVector<QVector<QString>>plannedNewStops; // naplanovane zastavky na trase
    bool set = false; // nastaveni barvy ulice a zpozdeni
    Street* current; // soucasna ulice
    int currentStops = 0; // kolik zastavek jsem jiz navstivil
    QMap<QString, Street*> streets; // ulice na ceste
    QString name; // nazev bus
    QString id; // identifikator busu
    float posX; // pozice v X
    float posY; // pozice v X
    float xStep; // krok v X
    float yStep; // krok v Y
    QVector<QString> stopsOnRoute; // zastavky na ceste

    /**
     * @brief Bus::countStreetLenght Vypocita a vrati dlzku cesty
     * @param street Pointer na objekt cesty
     * @return Vrati dlzku cesty
     */
    float countStreetLenght( Street* street );
    float step;     // krok na ceste
    float streetLength = 0; // delka ulice
    /**
     * @brief Bus::countStreetLenght Vypocita a vrati dlzku cesty
     * @param sx start ulice v x
     * @param sy start ulice v y
     * @param ex konec ulice v x
     * @param ey konec ulice v y
     */
    void countAdditions( float sx, float sy, float ex, float ey );
    float hypotenuse = 0; // prepona cesty
    float rest = 0; // zastavka na ceste
    bool useRest = false; // jestlize se ma bus zastavit na zastavce na ulici
    bool stopAtStop = false; // jestlize ma zustat stat na zastavce
    bool changeStop = false; // zmena zastavky

    /**
     * @brief Bus::countDistanceToStop
     * @return  vrati vzdialenost do najblizsej zastavky
     */
    float countDistanceToStop();
    float length = 0; // vzdalenost do dalsi zastavky
    bool halflength = false;

    /**
     * @brief Bus::timeToNext
     * @return Vrati cas do dalsieho pohybu autobusu
     */
    int timeToNext();

public:
    bool switchStop = false; // jestlize se ma prepsat seznam zastavek na zastavce pro objizdku
    bool switchNow = false; // jestli se ma zmenit nyni
    /**
     * @brief Bus::setNewStreeets nastavuje novou cestu pro autobus
     * @param plannedNStops vektor vektoru s informacemi o ceste
     */
    void setNewStreeets( QVector<QVector<QString>>plannedNStops );
    int newTime = 0;    // cas
    bool refactorRoute = false; // prepocet delky cesty
    bool refactor = false; // prepocet zastavek
    int timeFromStop = 0; // uplnynuly cas od zastavek
    int currentiCorrection = 0; //
    int currenti;   // index soucasne ulice
    QVector<Street*> route; // cesta
    /**
     * @brief Bus::clearRoute vycisti vektor cest
     * @param plannedNStops vektor vektoru s informacemi o ceste
     */
    void clearRoute();
    int delay = 0;  //!< zpozdeni
    bool enRoute = false; //!< jestlize se nachazi na ceste
    bool stationary = false; //!< jestlize stoji
    bool newRound = false; //!< je v cilove zastavce
    QString departure;  //!< id zastavky odjezdu

    /**
     * @brief Bus::boundingRect Vytvori kruh, znacku autobusu
     * @return Vracia objekt, kruh
     */
    QRectF boundingRect() const override;

    /**
     * @brief Bus::paint Vykreslenie kruhu
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QGraphicsEllipseItem* bus{nullptr}; //!< grafika busu

    /**
     * @brief Bus Konstruktor, vrati instanci na bus
     */
    Bus();

    /**
     * @brief Bus::getStreets Nastavi
     * @param str
     */
    void getStreets( QMap<QString, Street*> str );

    /**
     * @brief Bus::getBus
     * @return Vrati pointer na widget kruhu zanzornujuceho autobus
     */
    QGraphicsEllipseItem* getBus();

    /**
     * @brief Bus::getRoute
     * @return  vracia odkaz na trasu
     */
    QVector<Street *> getRoute();

    /**
     * @brief Bus::setRout nastavienie trasy
     * @param streetId ID ulice
     */
    void setRout( QString streetId );

    /**
     * @brief Bus::NameIt nastavenie mena
     * @param streetName
     */
    void NameIt( QString streetName );

    /**
     * @brief Bus::IdIt nastavenie id
     * @param ID
     */
    void IdIt( QString ID );

    /**
     * @brief Bus::GetPossition Vrati poziciu zaciatocnej stanice autobusu
     * @return Vracia objekt typu QPointF
     */
    QPointF GetPossition();

    /**
     * @brief Bus::setBus Nastavi polohu autobusu na mape
     */
    void setBus();

    /**
     * @brief Bus::getPos Vrati aktualnu polohu autobusu
     * @return Vracia objekt typu QPointF
     */
    QPointF getPos();

    /**
     * @brief Bus::nextPos Zisti nasledujucu polohu autobusu
     */
    void nextPos();

    /**
     * @brief Bus::getId Vrati ID
     * @return
     */
    QString getId();

    /**
     * @brief Bus::getName Vrati meno
     * @return
     */
    QString getName();

    /**
     * @brief Bus::getMiddle Vrati stred ulice
     * @return Vrati objekt typu QPointF
     */
    QPointF getMiddle();

    /**
     * @brief Bus::setStart Nastavi cas vyjazdu
     * @param time Cas zaciatku
     */
    void setStart( QString time );

    /**
     * @brief Bus::getStart
     * @return Vrati cas vyjazdu
     */
    QString getStart();
    QString start; //!< v kolik zacal svoji jizdu
    bool onmap = false; //!< jestlize se nachazi na mape
    QString startTime; //!< v kolik vyjel
    QVector<stop*> stops; //!< zastavky na ceste

    /**
     * @brief Bus::getStops
     */
    void getStops();
    QVector<QVector<QString>>plannedStops; //!< naplanovane zastavky
    int steps = 0;  //!< krok na ceste
    int now = 0; //!< index zastavky
    bool round = false; //!< kolo ulice
    bool atEnd = false; //!< nachazi se na konci

    /**
     * @brief Bus::setNul Inicializacia na povodne hodnoty pri skonceni trasy pre zacatie trasy znova
     */
    void setNul();

protected:

    /**
     * @brief Bus::mousePressEvent
     * @param event
     */
    void mousePressEvent( QGraphicsSceneMouseEvent *event ) override;

signals:
    /**
     * @brief valueChangedd Signal vytvoreny pri kliknuti na autobus.
     * @param stops Zastavky cez ktore autobus prechadza.
     * @param currentPos
     * @param route
     * @param stationary
     */
    void valueChangedd( QVector<QVector<QString>> stops, int currentPos, QVector<Street*> route, bool stationary );
};

#endif // BUS_H
