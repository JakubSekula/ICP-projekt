/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file mainwindow.h
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief hlavní grafické zobrazení
 */

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
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class Hlavní grafické zobrazení
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QMap<QString,int>delay; //!< zpodeni pro spawn busu
    int dly = 0; //!< nastaceni zpozdeni
    QVector<QGraphicsLineItem*> detour; //!< seznam objizdnych tras

    /**
     * @brief deleteMarked smazani oznacene trasy
     */
    void deleteMarked();
    int timerTime = 0; //!< cas na casovaci
    QMap<QString, QVector<Street*>> actuallLink; //!< linka
    QMap<QString, QVector<QVector<QString>>> actuallStops; //!< zastavky na trase
    /**
     * @brief getActualStops zmena zastavek
     * @param Bus ukazatel na bus tridu
     */
    QVector<QVector<QString>> getActualStops( Bus* bus );
    /**
     * @brief alternateRouteFunc zmena trasy
     */
    void alternateRouteFunc();
    /**
     * @brief convertToSec prevod casu na inkrementovanou hodnotu po 1
     */
    int convertToSec( int busDep, int delay );
    int convertToSec( int busDep );
    QTimer *timer; // cas
    QGraphicsItem* elipsa{ nullptr }; //!< ukazatel na grafiku zastavky
    QGraphicsItem* BusStop{ nullptr }; //!< ukazatel na grafiku zastavek
    QVector<Bus*> busses{nullptr}; //!< ukazatel na grafiku busu
    QMap<QString, QMap<QString, Bus*>> bussesHash; //!< mapa busu
    QMap<QString, line*> linkHash; //!< mapa linky
    QGraphicsScene* scene; //!< ukazatel do graficke sceny
    QTime lastTime; //!< rozdil casu oproti minulemu
    /**
     * @brief depart Jestli bus muze vyjet
     */
    bool depart( Bus* bus );
    QVector<QGraphicsLineItem*> pickedLines; //!< zvolene ulice
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
     * @param busses
     * @param lines
     */
    void initScene( QMap<QString, Street*> streets, QMap<QString, QMap<QString, Bus*>> busses, QMap<QString, line*> lines );

    /**
     * @brief MainWindow::spawnBus Pridanie autobusu do mapy na zaciatocnu zastavku
     */
    void spawnBus();
    QVector<Street*> alternateRoute; //!< Vektor ciest v obchadzke, prva cesta je uzavreta a ostatne su obchadzka
    /**
     * @brief replaceRoute Zmeni trasu busu
     */
    void replaceRoute();
    Ui::MainWindow *ui;//!< uzivatelske rozhranie
    MainWindow(QWidget *parent = nullptr); //!<Hlavni graficke zobrazeni
    ~MainWindow();


protected:
    /**
     * @brief mousePressEvent Funkcia pre zachytenie kliku mimo mapy
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
