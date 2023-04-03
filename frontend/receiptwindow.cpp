#include "receiptwindow.h"
#include "ui_receiptwindow.h"

ReceiptWindow::ReceiptWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiptWindow)
{
    ui->setupUi(this);
}

ReceiptWindow::~ReceiptWindow()
{
    delete ui;
}

void ReceiptWindow::on_buttonYes_clicked()
{
    emit clickReceipt(true);
}


void ReceiptWindow::on_buttonNo_clicked()
{
    emit clickReceipt(false);
}

