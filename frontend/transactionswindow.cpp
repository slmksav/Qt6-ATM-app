#include "transactionswindow.h"
#include "ui_transactionswindow.h"

TransactionsWindow::TransactionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionsWindow)
{
    ui->setupUi(this);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
}

void TransactionsWindow::updateUI()
{

}
