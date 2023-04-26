#include "spinner.h"
#include "ui_spinner.h"

Spinner::Spinner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spinner)
{
    ui->setupUi(this);

    QMovie* pMovie = new QMovie(":/exeimgs/gifigifigifigifi.gif");
    ui->label->setMovie(pMovie);
    pMovie->start();
}
Spinner::~Spinner()
{
    delete ui;
}
