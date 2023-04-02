#include "modeselectwindow.h"
#include "ui_modeselectwindow.h"

#include <QDebug>

ModeSelectWindow::ModeSelectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeSelectWindow)
{
    ui->setupUi(this);
}

ModeSelectWindow::~ModeSelectWindow()
{
    delete ui;
}

void ModeSelectWindow::on_buttonDebit_clicked()
{
    qDebug() << "Clicked debit";
    emit clickMode("debit");
}


void ModeSelectWindow::on_buttonCredit_clicked()
{
    qDebug() << "Clicked credit";
    emit clickMode("credit");
}

