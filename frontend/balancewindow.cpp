#include "balancewindow.h"
#include "ui_balancewindow.h"

BalanceWindow::BalanceWindow(QWidget *parent, SessionData *session) :
    QDialog(parent),
    ui(new Ui::BalanceWindow)
{
    ui->setupUi(this);

    this->session = session;

    session->resetTimer();

    updateUI();
}

BalanceWindow::~BalanceWindow()
{
    delete ui;

    session->resetTimer();
}

void BalanceWindow::updateUI()
{
    //debit and credit values
    if(session->accountType == "dual")
    {
        ui->labelBalance->setText(QString::number(session->accountBalance, 'f', 2));
        ui->labelCredit->setText(QString::number(session->accountCredit, 'f', 2));
    }
    else if(session->accountType == "debit")
    {
        ui->labelBalance->setText(QString::number(session->accountBalance, 'f', 2));
        ui->labelCredit->setText("-");
    }
    else
    {
        ui->labelBalance->setText("-");
        ui->labelCredit->setText(QString::number(session->accountCredit, 'f', 2));
    }

    //other ui elements
    if(session->language == "fi")
    {
        ui->buttonLogout->setText("Kirjaudu Ulos");
        ui->buttonReturn->setText("Palaa");

        ui->labelInfoBalance->setText("Saldo:");
        ui->labelInfoCredit->setText("Luotto:");
    }
    if(session->language == "en")
    {
        ui->buttonLogout->setText("Logout");
        ui->buttonReturn->setText("Return");

        ui->labelInfoBalance->setText("Balance:");
        ui->labelInfoCredit->setText("Credit:");
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

