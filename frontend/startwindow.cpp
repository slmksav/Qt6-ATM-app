
#include "startwindow.h"
#include "ui_startwindow.h"
#include <QDebug>

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_cardInput_textEdited(const QString &input)
{
    if (ui->cardInput->text().size() == 10)
    {
        qDebug() << "card input: " << input << "\tlen: " << ui->cardInput->text().size();

        //change this to signal to slot system
        int customerID = 3; //getCustomerID(input);
        //startSession(customerID);
        openPinCode();
    }
}

void StartWindow::logout()
{
    qDebug() << "Logout initiated";
    delete session;
    session = nullptr;
}

void StartWindow::openPinCode()
{
    pDLLPinCode = new DLLPinCode(this);
    pDLLPinCode->show();
}

void StartWindow::hidePinCode()
{
    pDLLPinCode->hide();
}

void StartWindow::printReceipt(bool print)
{
    //store transaction

    if(print)
    {
       //print transaction to a logfile or something else
    }

    logout();
}

void StartWindow::startSession(int customer)
{
    session = new SessionData();

    session->customerID = customer;

    //(defaulting some data for testing purposes)
    session->cardID = 2; //getCardID();
    session->accountID = 5; //getAccountID();
    session->accountType = "dual"; //getAccountType();
    session->customerName = "Markus Korhonen"; //getCustomerName();

    session->accountBalance = 255.64; //getAccountBalance();
    session->accountCredit = 500.00; //getAccountCredit();

    //getAdditionalAccountNames();
    session->additionalAccountNames = {"Martti Ahtisaari - debit",
                                       "Pekka Mahtisaari - dual",
                                       "Pertti Vahtisaari - credit",
                                       "Jorma Sahtisaari - debit",
                                       "Makkis Pekkis - dual",
                                       "Putte Possu - debit",
                                       "Poika Veli - credit"};

    //getAdditionalAccountIDs
    session->additionalAccountIDs = {3,6,13,102,103,222,345};

    foreach (QString var, session->additionalAccountNames) {
        qDebug() << var;
    }
    foreach (int var, session->additionalAccountIDs) {
        qDebug() << var;
    }

    if(session->accountType != "dual")
    {
        session->withdrawMode = session->accountType;
    }

    optionsWindow = new OptionsWindow(this);
    optionsWindow->putSessionData(session);
    optionsWindow->show();
}

void StartWindow::updateUI()
{

}

