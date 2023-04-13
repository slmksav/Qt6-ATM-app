
#include "startwindow.h"
#include "ui_startwindow.h"
#include <QDebug>

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    //language buttons
    connect(ui->buttonGroupLang, SIGNAL(idClicked(int)),
            this, SLOT(languageButtonClicked(int)));


    //create and connect signals from DLLSerialPort
    pDLLSerialPort = new DLLSerialPort;
    connect(pDLLSerialPort, SIGNAL(dataReceived(QString)),
            this, SLOT(openDLLPinCode(QString)));

    //create restapi dll class
    pDLLRestApi = new DLLRestApi();

    //test button signal to skip reading the card
    connect(this, SIGNAL(testOhitaKorttiSignal(QString)),
            this, SLOT(openDLLPinCode(QString)));

    //test button signal to skip pin window altogether
    connect(this, SIGNAL(testOhitaPINSignal(int)),
            this, SLOT(startSession(int)));

    QString imagePath = "C:/Pankkiautomaatti/group_18/englanninlippu.jpg"; // specify the file path of the image
    QString imagePath2 = "C:/Pankkiautomaatti/group_18/suomenlippu.png";
    QPixmap pixmap(imagePath);  // load the image from the file path
    QPixmap pixmap2(imagePath2);
    QIcon icon(pixmap);  // create an icon from the pixmap
    QIcon icon2(pixmap2);
    ui->buttonLangFI->setIcon(icon2);
    ui->buttonLangEN->setIcon(icon);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::languageButtonClicked(int buttonID)
{
    //get button value (text of the button)
    QString buttonValue = ui->buttonGroupLang->button(buttonID)->text();

    qDebug() << Q_FUNC_INFO << "Language selected: " << buttonValue;

    language = buttonValue;
}

void StartWindow::logout()
{
    qDebug() << Q_FUNC_INFO << "Logout initiated";

    delete optionsWindow;
    optionsWindow = nullptr;

    delete session;
    session = nullptr;
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
    qDebug() << Q_FUNC_INFO << "Got hexa from DLLSerialPort in StartWindow:" << hexaCode;
    pDLLPinCode = new DLLPinCode(this, hexaCode, language);

    connect(pDLLPinCode, SIGNAL(LoginSuccess(int)),
            this, SLOT(startSession(int)));

    pDLLPinCode->show();
}


void StartWindow::startSession(int returnedCardID)
{
    if(returnedCardID == 0)
    {
        qDebug() << Q_FUNC_INFO << "DLLPinCode returned" << returnedCardID <<
            "| startSession aborted...";
        return;
    }

    ui->labelInfo->setText("Odota...");

    //create new session
    session = new SessionData();
    session->cardID = returnedCardID;
    connect(session, SIGNAL(sendTimeout()),
            this, SLOT(logout()));

    if(returnedCardID == -333) //test case
    {
        session->accountID = -333;
        session->customerID = -333;
    }
    else
    {
        //this is unique in that it stays the same when changing accounts
        session->accountID = pDLLRestApi->getAccountId(session->cardID);
        //session->customerID = pDLLRestApi->getCustomerId(session->cardID);
    }

    //call DLLRestApi to get rest of the data
    fetchDataWithDLL(session->accountID);

    optionsWindow = new OptionsWindow(this);

    connect(session, SIGNAL(sendLogout()),
            this, SLOT(logout()));
    connect(optionsWindow, SIGNAL(changeToAccount(int)),
            this, SLOT(swapToAccount(int)));

    optionsWindow->putSessionData(session);
    optionsWindow->show();

    ui->labelInfo->setText("Lue Kortti");
}

void StartWindow::fetchDataWithDLL(int returnedAccountID)
{
    session->accountID = returnedAccountID;

    if(returnedAccountID == -333) //test button pressed, initiate test data
    {
        session->customerID = -333;
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
    else if(returnedAccountID == -222) //other test case
    {
        session->customerID = -222;
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
        session->customerID = pDLLRestApi->getCustomerId(session->accountID);
        session->accountType = pDLLRestApi->getAccountType(session->accountID);
        session->customerName = pDLLRestApi->getCustomerName(session->customerID);

        //avoid making unnecessary calls to server
        if(session->accountType == "dual")
        {
            session->accountBalance = pDLLRestApi->getAccountBalance(session->accountID);
            session->accountCredit = pDLLRestApi->getAccountCredit(session->accountID);
        }
        else if(session->accountType == "debit")
        {
            session->accountBalance = pDLLRestApi->getAccountBalance(session->accountID);
            session->accountCredit = 0.00;
        }
        else
        {
            session->accountBalance = 0.00;
            session->accountCredit = pDLLRestApi->getAccountCredit(session->accountID);
        }

        //dummy data, waiting for api function to get implemented
        session->additionalAccountNames = {"Martti Ahtisaari - debit",
                                           "Pekka Mahtisaari - dual",
                                           "Pertti Vahtisaari - credit",
                                           "Jorma Sahtisaari - debit",
                                           "Makkis Pekkis - dual",
                                           "Putte Possu - debit",
                                           "Poika Veli - credit"};

        //dummy data, waiting for api function to get implemented
        session->additionalAccountIDs = {3,6,13,102,103,-222,345};

        //dummy data, waiting for api function to get implemented
        session->transactionIDs = {1,2,3,4,
                                   5,6,7,8};
        session->transactionDates = {"01.02.2012", "05.12.2013", "01.12.2014", "06.11.2015",
                                     "01.12.2016", "05.10.2018", "01.02.2019", "05.12.2021"};
        session->transactionAmounts = {200.25, 55.00, 60, 20,
                                       20000.1, 60, 100.0, 100.00};
    }

    //put accountType to withdrawMode automatically if card isn't "dual"
    if(session->accountType != "dual")
    {
        session->withdrawMode = session->accountType;
    }

    session->debugPrintData();
}

void StartWindow::swapToAccount(int accountID)
{
    delete optionsWindow;
    optionsWindow = nullptr;

    session->accountID = accountID;

    //call DLLRestApi to get rest of the data
    fetchDataWithDLL(session->accountID);

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
    emit testOhitaPINSignal(-333);
}
