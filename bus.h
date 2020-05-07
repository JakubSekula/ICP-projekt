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
#include <QObject>

class Bus : public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    bool set = false;
    Street* current;
    int currenti;
    int currentStops = 0;
    QMap<QString, Street*> streets;
    QVector<Street*> route;
    QString name;
    QString id;
    float posX;
    float posY;
    float xStep;
    float yStep;
    bool switcher = false;
    QVector<QString> stopsOnRoute;
    QVector<int> additions;

    /**
     * @brief Bus::countStreetLenght Vypocita a vrati dlzku cesty
     * @param street Pointer na objekt cesty
     * @return Vrati dlzku cesty
     */
    float countStreetLenght( Street* street );
    float speedCoef = 1;
    int stopnow = 0;
    int currentStop = 0;
    float diffx = 0;
    float diffy = 0;
    float step;
    float streetLength = 0;
    void countAdditions( float sx, float sy, float ex, float ey );
    float hypotenuse = 0;
    float rest = 0;
    bool useRest = false;
    bool stopAtStop = false;
    bool changeStop = false;
    int streetWithStop = 0;

    /**
     * @brief Bus::countDistanceToStop
     * @return  vrati vzdialenost do najblizsej zastavky
     */
    float countDistanceToStop();
    float length = 0;
    bool halflength = false;

    /**
     * @brief Bus::timeToNext
     * @return Vrati cas do dalsieho pohybu autobusu
     */
    int timeToNext();

public:
    int delay = 0;
    bool enRoute = false;
    bool stationary = false;
    bool newRound = false;
    QString departure;

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
    QGraphicsEllipseItem* bus{nullptr};

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
    QString start;
    bool onmap = false;
    QString startTime;
    QVector<stop*> stops;

    /**
     * @brief Bus::getStops
     */
    void getStops();
    QVector<QVector<QString>>plannedStops;
    QMap<int,QVector<float>>test;
    int steps = 0;
    int now = 0;
    bool round = false;
    bool atEnd = false;

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
    void valueChangedd( QVector<QVector<QString>> stops, int currentPos, QVector<Street*> route, bool stationary );
};

#endif // BUS_H
