#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMouseEvent>
#include <QTimer>
#include <QGraphicsItem>
#include <QPainter>
#include "street.h"
#include "line.h"
#include "bus.h"
#include "readcsv.h"
#include <vector>
#include <QTransform>
#include "ui_mainwindow.h"
#include <QDebug>
#include <iterator>
#include <QWidget>
#include <QString>
#include <QDateTime>
#include <QVectorIterator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QMap<QString, QVector<Street*>> actuallLink;
    QMap<QString, QVector<QVector<QString>>> actuallStops;
    QVector<QVector<QString>> getActualStops( Bus* bus );
    void alternateRouteFunc();
    int convertDelay( int delay );
    QTimer *timer;
    int multiple = 1;
    QGraphicsItem* elipsa{ nullptr };
    QGraphicsItem* BusStop{ nullptr };
    QVector<Bus*> busses{nullptr};
    float posX = 504;
    float posY = 217;
    int posEX = 469;
    int posEY = 245;
    QRectF bStop;
    QMap<int, line*> lines;
    friend class Bus;
    QMap<QString, QMap<QString, Bus*>> bussesHash;
    QMap<QString, line*> linkHash;
    QGraphicsScene* scene;
    QTime lastTime;
    int jump;
    bool depart( Bus* bus );
    QVector<QGraphicsLineItem*> pickedLines;
    /**
     * @brief clearPicked Zrusenie zvyraznenia trasy po ktorej ide autobus
     */
    void clearPicked();
    bool changingLink = false; //!< Ci je aktivny stav klikania obchadzky

private slots:

    /**
     * @brief zoom Zvacsovanie mapy
     * @param x Zvacsenie
     */
    void zoom( int x );
    /**
     * @brief get_time Zistenie casu a zabezpecenie pohybu autobusu.
     */
    void get_time();

    /**
     * @brief speed Nastavnie rychlosti simulacie
     * @param x Zrychlenie
     */
    void speed( int x );

    /**
     * @brief MainWindow::BusMovement Vykreslovanie autobusu, pohyb autobusu
     */
    void BusMovement();
    /**
     * @brief resetBtnChecked Funkcia pre tlacidlo Reset. Zresetuje mapu a vsetko da do povodneho stavu.
     */
    void resetBtnChecked();
    /**
     * @brief linkBtnChecked Funkcia pre tlacidlo na zmenu trasy.
     */
    void linkBtnChecked();
    /**
     * @brief BusSignal Funkcia na zvyraznenie trasy pri kliknuti na autobus
     * @param stops Zastavky cez ktore autobus prechadza
     * @param currTime
     * @param route
     * @param inStation
     */
    void BusSignal( QVector<QVector<QString>> stops, int currTime, QVector<Street*> route, bool inStation );
    /**
     * @brief drawCross Funkcia pre zmeny farby cesty a vykreslenie krizu na uzvretu cestu.
     * @param middle Stred oznacenej cesty
     * @param s Cesta
     */
    void drawCross(coordinate* middle, Street *s);
    /**
     * @brief backColor Funkcia pre zrusenie oznacenia cesty pre obchadzku.
     * @param s Cesta
     */
    void backColor(Street* s);

public:

    /**
     * @brief MainWindow::initScene Vykreslenie mapy
     * @param streets
     * @param bussesHash
     * @param linkHash
     */
    void initScene( QMap<QString, Street*> streets, QMap<QString, QMap<QString, Bus*>> busses, QMap<QString, line*> lines );

    /**
     * @brief MainWindow::spawnBus Pridanie autobusu do mapy na zaciatocnu zastavku
     */
    void spawnBus();
    QVector<Street*> alternateRoute; //!< Vektor ciest v obchadzke, prva cesta je uzavreta a ostatne su obchadzka
    void replaceRoute();
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void test();


protected:
    /**
     * @brief mousePressEvent Funkcia pre zachytenie kliku mimo mapy
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
