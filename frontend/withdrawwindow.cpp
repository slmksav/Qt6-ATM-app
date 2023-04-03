#include "withdrawwindow.h"
#include "ui_withdrawwindow.h"

#include <QDebug>

WithdrawWindow::WithdrawWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WithdrawWindow)
{
    ui->setupUi(this);

    connect(ui->buttonGroup, SIGNAL(idClicked(int)),
            this, SLOT(withdrawButtonClicked(int)));
}

WithdrawWindow::~WithdrawWindow()
{
    delete ui;
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

void WithdrawWindow::putSessionData(SessionData *session)
{
    this->session = session;
    updateUI();
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

    qDebug() << "Withdrawal amount selected: " << buttonValue;
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
            qDebug() << "withdrawAmount exceeds accountBalance!\n"
                     << "Balance: " << session->accountBalance
                     << "After attempted withdrawal: " << newAmount;

            invalidAttempt = true;
            updateUI();
            return;
        }

        qDebug() << "Old accountBalance: " << session->accountBalance;
        session->accountBalance = newAmount;
        qDebug() << "New accountBalance: " << session->accountBalance;

        //setAccountBalance(session->accountID, session->accountBalance);
    }
    else
    {
        double newAmount = session->accountCredit - (double)amount;

        if(newAmount < 0.00)
        {
            qDebug() << "withdrawAmount exceeds accountCredit!\n"
                     << "Balance: " << session->accountCredit
                     << "After attempted withdrawal: " << newAmount;

            invalidAttempt = true;
            updateUI();
            return;
        }

        qDebug() << "Old accountCredit: " << session->accountCredit;
        session->accountCredit = newAmount;
        qDebug() << "New accountCredit: " << session->accountCredit;

        //setAccountCredit(session->accountID, session->accountCredit);
    }

    receiptWindow = new ReceiptWindow(this);
    receiptWindow->open();
}

