
#include "startwindow.h"
#include "ui_startwindow.h"
#include <QDebug>

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    //create and connect signals from DLLSerialPort
    pDLLSerialPort = new DLLSerialPort;
    connect(pDLLSerialPort, SIGNAL(dataReceived(QString)),
            this, SLOT(openDLLPinCode(QString)));



    //test button signal to skip reading the card
    connect(this, SIGNAL(testOhitaKorttiSignal(QString)),
            this, SLOT(openDLLPinCode(QString)));

    //test button signal to skip pin window altogether
    connect(this, SIGNAL(testOhitaPINSignal(int)),
            this, SLOT(startSession(int)));
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::logout()
{
    qDebug() << "Logout initiated";
    delete session;
    session = nullptr;

    delete optionsWindow;
    optionsWindow = nullptr;
}

//this might be redundant
void StartWindow::printReceipt(bool print)
{
    //store transaction

    if(print)
    {
       //print transaction to a logfile or something else
    }

    logout();
}


void StartWindow::openDLLPinCode(QString hexaCode)
{
    qDebug() << "Got hexa from DLLSerialPort in StartWindow:" << hexaCode;
    pDLLPinCode = new DLLPinCode(this);

    connect(pDLLPinCode, SIGNAL(LoginSuccess(int)),
            this, SLOT(startSession(int)));

    pDLLPinCode->cardHexCode = hexaCode;
    pDLLPinCode->show();
}


void StartWindow::startSession(int returnedCardID)
{
    if(returnedCardID == 0)
    {
        qDebug() << "DLLPinCode returned" << returnedCardID <<
            "startSession aborted...";
        return;
    }

    ui->labelInfo->setText("Odota...");

    session = new SessionData();
    session->cardID = returnedCardID;

    //test button pressed, initiate test data
    if(returnedCardID == -313)
    {
        session->customerID = 2;
        session->accountID = 5;
        session->accountType = "dual";
        session->customerName = "Markus Korhonen";

        session->accountBalance = 255.64;
        session->accountCredit = 500.00;

        session->additionalAccountNames = {"Martti Ahtisaari - debit",
                                           "Pekka Mahtisaari - dual",
                                           "Pertti Vahtisaari - credit",
                                           "Jorma Sahtisaari - debit",
                                           "Makkis Pekkis - dual",
                                           "Putte Possu - debit",
                                           "Poika Veli - credit"};

        session->additionalAccountIDs = {3,6,13,102,103,-222,345};

        session->transactionIDs = {1,2,3,4,
                                   5,6,7,8};
        session->transactionDates = {"01.02.2012", "05.12.2013", "01.12.2014", "06.11.2015",
                                     "01.12.2016", "05.10.2018", "01.02.2019", "05.12.2021"};
        session->transactionAmounts = {200.25, 55.00, 60, 20,
                                       20000.1, 60, 100.0, 100.00};
    }
    else
    {
        //DLLRestApi functions should fetch stuff from database here
    }

    if(session->accountType != "dual")
    {
        session->withdrawMode = session->accountType;
    }

    optionsWindow = new OptionsWindow(this);

    connect(session, SIGNAL(sendLogout()),
            this, SLOT(logout()));
    connect(optionsWindow, SIGNAL(changeToAccount(int)),
            this, SLOT(swapToAccount(int)));

    optionsWindow->putSessionData(session);
    optionsWindow->show();
}

void StartWindow::swapToAccount(int accountID)
{
    delete optionsWindow;
    optionsWindow = nullptr;

    session->accountID = accountID;

    //test button pressed, initiate test data
    if(accountID == -222)
    {
//        session->customerID = 2;
//        session->accountID = 5;
        session->accountType = "debit";
        session->customerName = "Putte Possu";

        session->accountBalance = 155.62;
        session->accountCredit = 50000.00;

        session->additionalAccountNames = {"Martti Ahtisaari - debit",
                                           "Pekka Mahtisaari - dual",
                                           "Pertti Vahtisaari - credit"};

        session->additionalAccountIDs = {3,6,13};

        session->transactionIDs = {1,2,3,4,
                                   5,6,7,8};
        session->transactionDates = {"01.02.2015", "05.12.2016", "01.12.2017", "06.11.2018",
                                     "01.12.2019", "05.10.2020", "01.02.2021", "05.12.2022"};
        session->transactionAmounts = {100.25, 155.00, 160, 120,
                                       20000.11, 560, 1000.0, 200.00};
    }
    else
    {
        //DLLRestApi functions should fetch stuff from database here
    }

    if(session->accountType != "dual")
    {
        session->withdrawMode = session->accountType;
    }

    optionsWindow = new OptionsWindow(this);

    connect(session, SIGNAL(sendLogout()),
            this, SLOT(logout()));

    optionsWindow->putSessionData(session);
    optionsWindow->show();
}

void StartWindow::updateUI()
{

}

//This button shall get removed on release
void StartWindow::on_buttonOhitaKortti_clicked()
{
    emit testOhitaKorttiSignal("0d0a2d303630303035343246450d0a3e");
}

//This button shall get removed on release
void StartWindow::on_buttonOhitaPIN_clicked()
{
    emit testOhitaPINSignal(-313);
}

