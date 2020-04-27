#include "dialog.h"

Dialog::Dialog( QWidget *parent )
    : QDialog( parent )
    , ui(new Ui::Dialog)
{

}

Dialog::~Dialog()
{
    delete ui;
}
