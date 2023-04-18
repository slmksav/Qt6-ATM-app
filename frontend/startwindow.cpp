
#include "startwindow.h"
#include "ui_startwindow.h"
#include <QDebug>
#include <QGraphicsBlurEffect>
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
    connect(this, SIGNAL(testOhitaPINSignal(int,QString)),
            this, SLOT(startSession(int,QString)));

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StartWindow::updateTime); //connect to clock
    connect(timer, SIGNAL(timeout()),
            this, SLOT(expireTimedStates())); //connect to states
    timer->start(1000);

    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(4);
    ui->labelInfo->setGraphicsEffect(blurEffect);

    sound();
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::sound()
{
          player = new QMediaPlayer;
          audioOutput = new QAudioOutput;
          player->setAudioOutput(audioOutput);

          QString soundFilePath = QCoreApplication::applicationDirPath() + "/../../sounds/readcardFI.mp3";
          qDebug() << "Sound file path:" << soundFilePath;

          if (QFile::exists(soundFilePath)) {
              player->setSource(QUrl::fromLocalFile(soundFilePath));
              audioOutput->setVolume(0.5);  // set volume to 50%
              player->play();
          } else {
              qDebug() << "Sound file does not exist!";
          }
          audioOutput->setVolume(1);
          player->play();
}

void StartWindow::languageButtonClicked(int buttonID)
{
    //get button value (text of the button)
    QString buttonValue = ui->buttonGroupLang->button(buttonID)->text();

    qDebug() << Q_FUNC_INFO << "Language selected: " << buttonValue;

    language = buttonValue;
    updateUI();
}

void StartWindow::logout(QObject* initiator)
{
    qDebug() << Q_FUNC_INFO << "Logout initiated by" << initiator;
    qDebug() << Q_FUNC_INFO << "QObject::sender()" << QObject::sender();
    if(initiator == session)
    {
        qDebug() << Q_FUNC_INFO << "Session probably sent out a timeout signal";
        state = Timeout;
    }

    //delete windows before SessionData, because their destructors
    //make calls to SessionData's timeout() function, for example
    if(optionsWindow != nullptr && session != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "Deleting OptionsWindow";
        delete optionsWindow;
        optionsWindow = nullptr;
    }

    //!can only been deleted after windows have been deleted
    if(session != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "Deleting SessionData";
        delete session;
        session = nullptr;
    }

    if(state != Error && state != Timeout)
        state = Logout;

    updateUI();
}

void StartWindow::openDLLPinCode(QString hexaCode)
{
    if(state != Default)
    {
        qDebug() << Q_FUNC_INFO << "invalid state for card reading";
        return;
    }

    state = Running;

    qDebug() << Q_FUNC_INFO << "Got hexa from DLLSerialPort in StartWindow:" << hexaCode;
    pDLLPinCode = new DLLPinCode(this, hexaCode, language);

    connect(pDLLPinCode, SIGNAL(LoginSuccess(int,QString)),
            this, SLOT(startSession(int,QString)));

    pDLLPinCode->show();
}


void StartWindow::startSession(int returnedCardID, QString token)
{
    //returned invalid cardID
    if(returnedCardID <= 0)
    {
        qDebug() << Q_FUNC_INFO << "DLLPinCode returned" << returnedCardID <<
            "| startSession aborted...";
        state = Default;
        updateUI();

        return;
    }

    //put token to DLLRestApi
    pDLLRestApi->token = token;
    //update state and ui
    state = Waiting;
    updateUI();

    //create new session
    session = new SessionData();
    session->restApi = pDLLRestApi;
    session->stopTimer(); //stop until all data has been fetched from db
    session->language = language;
    session->cardID = returnedCardID;
    connect(session, SIGNAL(sendTimeout(QObject*)),
            this, SLOT(logout(QObject*)));

    //this is unique in that it stays the same even when changing accounts
    session->accountID = pDLLRestApi->getAccountId(session->cardID);

    //call DLLRestApi to get rest of the data
    fetchDataWithDLL(session->accountID);

    //check if data is valid
    if(session->checkDataValidity() == false)
    {
        state = Error;
        updateUI();
        logout(this);
        return;
    }

    //put info of person who logged in to memory
    session->originalAccountID = session->accountID;
    session->originalCustomerName = session->customerName;

    //create and show OptionsWindow
    openOptionsWindow();
}

void StartWindow::fetchDataWithDLL(int returnedAccountID)
{
    qDebug() << Q_FUNC_INFO << "Fetchind data with accountID: " << returnedAccountID;

    session->stopTimer();

    session->accountID = returnedAccountID;

    //DLLRestApi functions should fetch stuff from database here
    session->customerID = pDLLRestApi->getCustomerId(session->accountID);
    session->accountType = pDLLRestApi->getAccountType(session->accountID);
    session->customerName = pDLLRestApi->getCustomerName(session->customerID);

    //avoid making unnecessary calls to server
    if(session->accountType == "debit" || session->accountType == "dual")
    {
        session->accountBalance = pDLLRestApi->getAccountBalance(session->accountID);
    }
    if(session->accountType == "credit" || session->accountType == "dual")
    {
        session->accountCredit = pDLLRestApi->getAccountCredit(session->accountID);
        session->accountCreditMax = pDLLRestApi->getCreditMax(session->accountID);
    }

    //additional accounts
    session->additionalAccountIDs.clear();
    session->additionalAccountIDs.append(
        pDLLRestApi->getAdditionalAccountIDs(session->cardID));
    qDebug() << Q_FUNC_INFO << "Retrieved ID list size:" << session->additionalAccountIDs.count();

    session->additionalAccountNames.clear();
    session->additionalAccountNames.append(
        pDLLRestApi->getAdditionalAccountNames(session->cardID));
    qDebug() << Q_FUNC_INFO << "Retrieved names list size:" << session->additionalAccountNames.count();

    //transactions
    session->transactionIDs.clear();
    session->transactionIDs.append(
        pDLLRestApi->getTransactionIDs(session->accountID));
    qDebug() << Q_FUNC_INFO << "Retrieved transacID list size:" << session->transactionIDs.count();

    session->transactionDates.clear();
    session->transactionDates.append(
        pDLLRestApi->getTransactionDates(session->accountID));
    qDebug() << Q_FUNC_INFO << "Retrieved transac dates list size:" << session->transactionDates.count();

    session->transactionAmounts.clear();
    session->transactionAmounts.append(
        pDLLRestApi->getTransactionAmounts(session->accountID));
    qDebug() << Q_FUNC_INFO << "Retrieved transac amounts list size:" << session->transactionAmounts.count();

    //put accountType to withdrawMode automatically if card isn't "dual"
    if(session->accountType != "dual")
    {
        session->withdrawMode = session->accountType;
    }

    session->resetTimer();

    //debug print all session data
    session->debugPrintData();
}

void StartWindow::swapToAccount(int accountID)
{
    qDebug() << Q_FUNC_INFO << "Swapping account with accountID: " << accountID;

    //delete old windows
    delete optionsWindow;
    optionsWindow = nullptr;

    //update state and ui
    state = Waiting;
    updateUI();

    //accountID changes to new, selected account
    session->accountID = accountID;

    //call DLLRestApi to get rest of the data
    fetchDataWithDLL(session->accountID);

    //check if data is valid
    if(session->checkDataValidity() == false)
    {
        state = Error;
        updateUI();
        logout(this);
        return;
    }

    //create and show OptionsWindow
    openOptionsWindow();
}

void StartWindow::openOptionsWindow()
{
    //create and show OptionsWindow
    optionsWindow = new OptionsWindow(this, session);

    connect(session, SIGNAL(sendLogout(QObject*)),
            this, SLOT(logout(QObject*)));
    connect(optionsWindow, SIGNAL(changeToAccount(int)),
            this, SLOT(swapToAccount(int)));

    optionsWindow->show();

    //update state and ui
    state = Running;
    updateUI();
}

void StartWindow::updateUI()
{
    if(pSpinner != nullptr)
    {
        delete pSpinner;
        pSpinner = nullptr;  
    }

    switch (state) {
    case Default:
        if(language == "fi")
        {
            ui->labelInfo->setText("Lue kortti aloittaaksesi");
            ui->labelInfo2->setText("Lue kortti aloittaaksesi");
            ui->labelPhoneInfo->setText("Palvelunumero (ark. 8-17)");
        }
        if(language == "en")
        {
            ui->labelInfo->setText("Read card to begin");
            ui->labelInfo2->setText("Read card to begin");
            ui->labelPhoneInfo->setText("Service Number (WD 8-17)");
        }
        break;

    case Waiting:

        pSpinner = new Spinner;

        if(language == "fi")
        {
            ui->labelInfo->setText("Odota Hetki");
            ui->labelInfo2->setText("Odota Hetki");
        }
        if(language == "en")
        {
            ui->labelInfo->setText("Wait a Moment");
            ui->labelInfo2->setText("Wait a Moment");
        }
        break;

    case Running:

        break;

    case Timeout:
        if(language == "fi")
        {
            ui->labelInfo->setText("Kirjauduttu Ulos\n"
                                   "Inaktiivisuuden Vuoksi");
            ui->labelInfo2->setText("Kirjauduttu Ulos\n"
                                   "Inaktiivisuuden Vuoksi");
        }
        if(language == "en")
        {
            ui->labelInfo->setText("Logged Out\n"
                                   "Due to Inactivity");
            ui->labelInfo2->setText("Logged Out\n"
                                   "Due to Inactivity");
        }
        break;

    case Error:
        if(language == "fi")
        {
            ui->labelInfo->setText("Odottamaton Virhe\n"
                                   "Yritä Uudestaan");
            ui->labelInfo2->setText("Odottamaton Virhe\n"
                                   "Yritä Uudestaan");
        }
        if(language == "en")
        {
            ui->labelInfo->setText("Unexpected Error\n"
                                   "Try Again");
            ui->labelInfo2->setText("Unexpected Error\n"
                                   "Try Again");
        }
        break;

    case Logout:
        if(language == "fi")
        {
            ui->labelInfo->setText("Kiitos Asioinnista");
            ui->labelInfo2->setText("Kiitos Asioinnista");
        }
        if(language == "en")
        {
            ui->labelInfo->setText("Thank You for\n"
                                   "Using Our Service");
            ui->labelInfo2->setText("Thank You for\n"
                                   "Using Our Service");
        }
        break;

    default:
        qDebug() << Q_FUNC_INFO << "updateUI switch-case defaulted";
        break;
    }
}

//This button shall get removed on release
void StartWindow::on_buttonOhitaKortti_clicked()
{
    emit testOhitaKorttiSignal("0d0a2d303630303035343246450d0a3e");
}

//This button shall get removed on release
void StartWindow::on_buttonOhitaPIN_clicked()
{
    qDebug() << Q_FUNC_INFO << "";

    QString hex = "0d0a2d303630303035343246450d0a3e";
    QString pin = "1234";

    if(!pDLLRestApi->postLogin(hex, pin))
    {
        qDebug() << Q_FUNC_INFO << "wrong login info";
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "correct login info";
    }

    emit testOhitaPINSignal(2, "testtoken");
}

void StartWindow::updateTime()
{
    // Get the current time
    QDateTime currentTime = QDateTime::currentDateTime();

    // Update the QLabel with the time
    ui->labelTime->setText(currentTime.toString("hh:mm:ss"));
}

void StartWindow::expireTimedStates()
{
    //not a timed state
    if(state == Default || state == Waiting || state == Running)
    {
        return;
    }

    //count to n seconds and then set state to Default
    static int countSeconds;
    countSeconds++;

    if(countSeconds >= 10)
    {
        qDebug() << Q_FUNC_INFO << "expiring timed states";
        countSeconds = 0;
        state = Default;
        updateUI();
    }
}
