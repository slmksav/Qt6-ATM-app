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
    if(session->accountType == "dual")
    {
        ui->labelBalance->setText(QString::number(session->accountBalance));
        ui->labelCredit->setText(QString::number(session->accountCredit));
    }
    else if(session->accountType == "debit")
    {
        ui->labelBalance->setText(QString::number(session->accountBalance));
        ui->labelCredit->setText("-");
    }
    else
    {
        ui->labelBalance->setText("-");
        ui->labelCredit->setText(QString::number(session->accountCredit));
    }
}


void BalanceWindow::on_buttonLogout_clicked()
{
    emit session->sendLogout();
}


void BalanceWindow::on_buttonReturn_clicked()
{
    done(Accepted);
}

