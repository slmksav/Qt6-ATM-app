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

void TransactionsWindow::putSessionData(SessionData *session)
{
    this->session = session;
    updateUI();
}

void TransactionsWindow::updateUI()
{

}

void TransactionsWindow::on_buttonLogout_clicked()
{
    emit session->sendLogout();
}

