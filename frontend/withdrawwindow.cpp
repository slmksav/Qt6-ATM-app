#include "withdrawwindow.h"
#include "ui_withdrawwindow.h"

#include <QDebug>

WithdrawWindow::WithdrawWindow(QWidget *parent, SessionData *session) :
    QDialog(parent),
    ui(new Ui::WithdrawWindow)
{
    ui->setupUi(this);

    this->session = session;

    session->resetTimer();

    updateUI();

    connect(ui->buttonGroup, SIGNAL(idClicked(int)),
            this, SLOT(withdrawButtonClicked(int)));
}

WithdrawWindow::~WithdrawWindow()
{
    delete ui;

    session->resetTimer();
}

void WithdrawWindow::updateUI()
{
    ui->labelWithdrawInfo->setText(session->customerName + " - " + session->withdrawMode);

    if(invalidAttempt == true)
    {
        if(session->language == "fi")
        {
            if(session->withdrawMode == "debit")
            {
                ui->labelWithdrawWarning->setText("Kate ei riitä!");
            }
            else
            {
                ui->labelWithdrawWarning->setText("Luotto ei riitä!");
            }
        }
        if(session->language == "en")
        {
            if(session->withdrawMode == "debit")
            {
                ui->labelWithdrawWarning->setText("Balance is not Sufficient!");
            }
            else
            {
                ui->labelWithdrawWarning->setText("Credit is not Sufficient!");
            }
        }
    }
    else
    {
        ui->labelWithdrawWarning->setText("");
    }

    //other ui elements
    if(session->language == "fi")
    {
        ui->buttonLogout->setText("Kirjaudu Ulos");
        ui->buttonReturn->setText("Palaa");
    }
    if(session->language == "en")
    {
        ui->buttonLogout->setText("Logout");
        ui->buttonReturn->setText("Return");
    }
}

void WithdrawWindow::withdrawButtonClicked(int buttonID)
{
    //get button value (text of the button)
    int buttonValue = ui->buttonGroup->button(buttonID)->text().toInt();

    qDebug() << Q_FUNC_INFO << "Withdrawal amount selected: " << buttonValue;
    withdrawMoney(buttonValue);
}

void WithdrawWindow::withdrawMoney(int amount)
{
    session->withdrawAmount = amount;

    if(session->withdrawMode == "debit")
    {
        double newAmount = session->accountBalance - (double)amount;

        if(newAmount < 0.00)
        {
            qDebug() << Q_FUNC_INFO << "withdrawAmount exceeds accountBalance!\n"
                     << "\tBalance: " << session->accountBalance
                     << "| After attempted withdrawal: " << newAmount;

            invalidAttempt = true;
            updateUI();
            return;
        }

        qDebug() << Q_FUNC_INFO << "Old accountBalance: " << session->accountBalance;
        session->accountBalance = newAmount;
        qDebug() << Q_FUNC_INFO << "New accountBalance: " << session->accountBalance;

        //setAccountBalance(session->accountID, session->accountBalance);
    }
    else
    {
        double newAmount = session->accountCredit - (double)amount;

        if(newAmount < 0.00)
        {
            qDebug() << Q_FUNC_INFO << "withdrawAmount exceeds accountCredit!\n"
                     << "\tBalance: " << session->accountCredit
                     << "| After attempted withdrawal: " << newAmount;

            invalidAttempt = true;
            updateUI();
            return;
        }

        qDebug() << Q_FUNC_INFO << "Old accountCredit: " << session->accountCredit;
        session->accountCredit = newAmount;
        qDebug() << Q_FUNC_INFO << "New accountCredit: " << session->accountCredit;

        //setAccountCredit(session->accountID, session->accountCredit);
    }

    receiptWindow = new ReceiptWindow(this, session);
    receiptWindow->open();
}


void WithdrawWindow::on_buttonLogout_clicked()
{
    emit session->sendLogout();
}


void WithdrawWindow::on_buttonReturn_clicked()
{
    done(Accepted);
}

