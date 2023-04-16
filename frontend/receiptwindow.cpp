#include "receiptwindow.h"
#include "ui_receiptwindow.h"

ReceiptWindow::ReceiptWindow(QWidget *parent, SessionData *session) :
    QDialog(parent),
    ui(new Ui::ReceiptWindow)
{
    ui->setupUi(this);

    this->session = session;

    session->resetTimer();

    updateUI();
}

ReceiptWindow::~ReceiptWindow()
{
    delete ui;

    session->resetTimer();
}

void ReceiptWindow::updateUI()
{
    //other ui elements
    if(session->language == "fi")
    {
        ui->labelInfo->setText("Haluatko kuitin??");
        ui->buttonYes->setText("Kyllä");
        ui->buttonNo->setText("En");
    }
    if(session->language == "en")
    {
        ui->labelInfo->setText("Do you want a receipt?");
        ui->buttonYes->setText("Yes");
        ui->buttonNo->setText("No");
    }

}

void ReceiptWindow::on_buttonYes_clicked()
{
    QString log = generateLog();

    session->restApi->postEmail(session->accountID, log); //todo: include cardowner name

    emit session->sendLogout();
}


void ReceiptWindow::on_buttonNo_clicked()
{
    emit session->sendLogout();
}

QString ReceiptWindow::generateLog()
{
    QString log;
    QDate date;

    log.append("Date: " + date.currentDate().toString());
    log.append("\nAccount: " + session->customerName + " - " + session->accountType);
    log.append("\n");

    if(session->withdrawMode == "debit")
    {
        log.append("\nDebit withdrawal: "
                   + QString::number((session->accountBalance + session->withdrawAmount), 'f', 2)
                   + " - " + QString::number(session->withdrawAmount, 'f', 2));
        log.append("\nAfter withdrawal: " + QString::number(session->accountBalance, 'f', 2));
    }
    else
    {
        log.append("\nCredit withdrawal: "
                   + QString::number((session->accountCredit - session->withdrawAmount), 'f', 2)
                   + " + " + QString::number(session->withdrawAmount, 'f', 2));
        log.append("\nUsed credit after withdrawal: " + QString::number(session->accountCredit, 'f', 2));
        log.append("\nCredit cap: " + QString::number(session->accountCreditMax, 'f', 2));
    }
    log.append("\n");

    qDebug() << Q_FUNC_INFO << log;

    return log;
}

