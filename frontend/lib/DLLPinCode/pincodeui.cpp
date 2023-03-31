#include "pincodeui.h"
#include "ui_pincodeui.h"

PinCodeUi::PinCodeUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PinCodeUi)
{
    ui->setupUi(this);
}

PinCodeUi::~PinCodeUi()
{
    delete ui;
}
