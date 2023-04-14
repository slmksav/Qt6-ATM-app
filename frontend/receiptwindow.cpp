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

}

void ReceiptWindow::on_buttonYes_clicked()
{
    //emit clickReceipt(true); //lets maybe handle logging in this class instead

    //handle logfile code below please

    //

    emit session->sendLogout();
}


void ReceiptWindow::on_buttonNo_clicked()
{
    //emit clickReceipt(false);

    emit session->sendLogout();
}

