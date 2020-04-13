#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void zoom( int x );

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void initScene( QVector<QVector<int>> lines, int iter );
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
