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
    //quick maths
    //decimate withdrawable sums
    double balanceAvailable = 0.00;
    double creditAvailable = 0.00;
    if(session->accountType == "debit" || session->accountType == "dual")
    {
        balanceAvailable = session->accountBalance;
        qDebug() << Q_FUNC_INFO << "(int)(session->accountBalance * 100) % 1000 = "
                 << (int)(balanceAvailable * 100) % 1000;

        double cutoff = (int)(balanceAvailable * 100) % 1000;
        balanceAvailable -= cutoff / 100.0;

        qDebug() << Q_FUNC_INFO << "balanceAvailable: " << balanceAvailable;
    }
    if(session->accountType == "credit" || session->accountType == "dual")
    {
        creditAvailable = session->accountCreditMax - session->accountCredit;
        qDebug() << Q_FUNC_INFO << "(int)(creditAvailable * 100) % 1000 = "
                 << (int)(creditAvailable * 100) % 1000;

        double cutoff = (int)(creditAvailable * 100) % 1000;
        creditAvailable -= cutoff / 100.0;

        // jos voi nostaa vähemmön kuin 20, niin ei voi nostaa oikeasti ollenkaan. Eli pistetään nollaksi se paljon voi nostaa.
        if (creditAvailable < 20) {
            creditAvailable = 0;
        }

        qDebug() << Q_FUNC_INFO << "creditAvailable: " << creditAvailable;
    }


    //actual ui stuff below
    //debit and credit values
    if(session->accountType == "dual")
    {
        ui->labelBalance->setText(QString::number(session->accountBalance, 'f', 2));
        ui->labelCredit->setText(QString::number(session->accountCredit, 'f', 2));
        ui->labelCreditMax->setText(QString::number(session->accountCreditMax, 'f', 2));

        ui->labelBalanceAvail->setText(QString::number(balanceAvailable, 'f', 2));
        ui->labelCreditAvail->setText(QString::number(creditAvailable, 'f', 2));
    }
    else if(session->accountType == "debit")
    {
        ui->labelBalance->setText(QString::number(session->accountBalance, 'f', 2));
        ui->labelCredit->setText("-");
        ui->labelCreditMax->setText("-");

        ui->labelBalanceAvail->setText(QString::number(balanceAvailable, 'f', 2));
        ui->labelCreditAvail->setText("-");
    }
    else
    {
        ui->labelBalance->setText("-");
        ui->labelCredit->setText(QString::number(session->accountCredit, 'f', 2));
        ui->labelCreditMax->setText(QString::number(session->accountCreditMax, 'f', 2));

        ui->labelBalanceAvail->setText("-");
        ui->labelCreditAvail->setText(QString::number(creditAvailable, 'f', 2));
    }

    //other ui elements
    if(session->language == "fi")
    {
        ui->buttonLogout->setText("Kirjaudu Ulos");
        ui->buttonReturn->setText("Palaa");

        ui->labelInfoBalance->setText("Saldo:");
        ui->labelInfoCredit->setText("Käytetty Luotto:");
        ui->labelInfoCreditMax->setText("Luottokatto:");

        ui->labelInfoBalanceAvail->setText("Nostettavissa:");
        ui->labelInfoCreditAvail->setText("Nostettavissa:");
    }
    if(session->language == "en")
    {
        ui->buttonLogout->setText("Logout");
        ui->buttonReturn->setText("Return");

        ui->labelInfoBalance->setText("Balance:");
        ui->labelInfoCredit->setText("Used Credit:");
        ui->labelInfoCreditMax->setText("Credit Cap:");

        ui->labelInfoBalanceAvail->setText("Withdrawable:");
        ui->labelInfoCreditAvail->setText("Withdrawable:");
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

