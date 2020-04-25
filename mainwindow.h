#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMouseEvent>
#include <QTimer>
#include <QGraphicsItem>
#include <QPainter>
#include "street.h"

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
    float posX = 239;
    float posY = 342;
    QRectF test;
    QGraphicsEllipseItem * Bus;

private slots:
    void zoom( int x );
    void get_time();
    void speed( int x );

public:
    void initScene( QMap<QString, Street*> streets );
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
