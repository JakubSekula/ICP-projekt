#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include "ui_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT;
public:
    Dialog(QWidget *parent = nullptr);
    Ui::Dialog *ui;
    ~Dialog();;
};

#endif // DIALOG_H
