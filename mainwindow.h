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

private slots:

    /**
     * @brief zoom Zvacsovanie mapy
     * @param x Zvacsenie
     */
    void zoom( int x );
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
    void BusSignal( QVector<QVector<QString>> stops );

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
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void test();
};
#endif // MAINWINDOW_H
