#include "spinner.h"
#include "ui_spinner.h"

Spinner::Spinner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Spinner)
{
    ui->setupUi(this);
    QDialog* pDialog = new QDialog(this);
    pDialog->resize(801, 481);
    QLabel* pLabel = new QLabel(pDialog);
    QMovie* pMovie = new QMovie(":/exeimgs/gifigifigifigifi.gif");
    pLabel->setMovie(pMovie);
    pMovie->start();
    QVBoxLayout* layout = new QVBoxLayout(pDialog);
    layout->addWidget(pLabel);
    layout->setAlignment(Qt::AlignCenter); // center the label in the layout
    pDialog->setLayout(layout);
    pDialog->show();
}
Spinner::~Spinner()
{
    delete ui;
}
