#include "spinner.h"
#include "ui_spinner.h"

Spinner::Spinner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Spinner)
{
    ui->setupUi(this);
    QWidget::showFullScreen();

    QMovie* pMovie = new QMovie(":/exeimgs/gifigifigifigifi.gif");
    ui->label->setMovie(pMovie);
    pMovie->start();
}
Spinner::~Spinner()
{
    delete ui;
}
