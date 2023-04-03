#include "balancewindow.h"
#include "ui_balancewindow.h"

BalanceWindow::BalanceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BalanceWindow)
{
    ui->setupUi(this);
}

BalanceWindow::~BalanceWindow()
{
    delete ui;
}

void BalanceWindow::putSessionData(SessionData *session)
{
    this->session = session;
    updateUI();
}

void BalanceWindow::updateUI()
{

}
