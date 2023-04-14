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

void WithdrawWindow::withdrawExceedWarning()
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

void WithdrawWindow::updateUI()
{
    ui->labelWithdrawInfo->setText(session->customerName + " - " + session->withdrawMode);

    if(invalidAttempt == true)
    {
        withdrawExceedWarning();
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

