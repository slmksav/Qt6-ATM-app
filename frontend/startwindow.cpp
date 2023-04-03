
#include "startwindow.h"
#include "ui_startwindow.h"
#include <QDebug>

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    //optionsWindow connections
    optionsWindow = new OptionsWindow(this);

    connect(optionsWindow, SIGNAL(clickLogout()),
            this, SLOT(logout()));

    connect(optionsWindow, SIGNAL(clickWithdraw()),
            this, SLOT(openWithdraw()));

    connect(optionsWindow, SIGNAL(clickBalance()),
            this, SLOT(openBalance()));

    connect(optionsWindow, SIGNAL(clickTransactions()),
            this, SLOT(openTransactions()));

    connect(optionsWindow, SIGNAL(clickChangeAccount()),
            this, SLOT(openChangeAccount()));

    //withdrawWindow connections
    withdrawWindow = new WithdrawWindow(this);
    connect(withdrawWindow, SIGNAL(clickAmount(int)),
            this, SLOT(withdrawMoney(int)));

    //balanceWindow connections
    balanceWindow = new BalanceWindow(this);

    //transactionsWindow connections
    transactionsWindow = new TransactionsWindow(this);

    //changeAccountWindow connections
    changeAccountWindow = new ChangeAccountWindow(this);


    //modeSelectWindow connections
    modeSelectWindow = new ModeSelectWindow(this);

    connect(modeSelectWindow, SIGNAL(clickMode(QString)),
            this, SLOT(changeWithdrawType(QString)));

    //receiptWindow connections
    receiptWindow = new ReceiptWindow(this);

    connect(receiptWindow, SIGNAL(clickReceipt(bool)),
            this, SLOT(printReceipt(bool)));


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
        startSession(customerID);
    }
}

void StartWindow::logout()
{
    qDebug() << "Logout initiated";
    delete session;
    session = nullptr;
}

void StartWindow::openWithdraw()
{
    if(session->accountType == "dual")
    {
        openModeSelect();
    }
    else
    {
        withdrawWindow->updateUI(session->accountType);
        withdrawWindow->show();
    }
}

void StartWindow::withdrawMoney(int amount)
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

            withdrawWindow->withdrawExceedWarning("debit");
            return;
        }

        qDebug() << "Old accountBalance: " << session->accountBalance;
        session->accountBalance = newAmount;
        qDebug() << "New accountBalance: " << session->accountBalance;
    }
    else
    {
        double newAmount = session->accountCredit - (double)amount;

        if(newAmount < 0.00)
        {
            qDebug() << "withdrawAmount exceeds accountCredit!\n"
                     << "Balance: " << session->accountCredit
                     << "After attempted withdrawal: " << newAmount;

            withdrawWindow->withdrawExceedWarning("credit");
            return;
        }

        qDebug() << "Old accountCredit: " << session->accountCredit;
        session->accountCredit = newAmount;
        qDebug() << "New accountCredit: " << session->accountCredit;
    }

    receiptWindow->open();
}

void StartWindow::openModeSelect()
{
    modeSelectWindow->show();
}

void StartWindow::changeWithdrawType(QString mode)
{
    session->withdrawMode = mode;
    qDebug() << "Withdraw mode changed to: " << session->withdrawMode;

    withdrawWindow->updateUI(session->accountType);
    withdrawWindow->show();
}

void StartWindow::openBalance()
{

}

void StartWindow::openTransactions()
{

}

void StartWindow::openChangeAccount()
{
    changeAccountWindow->updateUI(session->additionalAccountNames);
    changeAccountWindow->show();
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

    optionsWindow->updateUI(session->customerName, session->accountType);
    optionsWindow->show();
}

void StartWindow::updateUI()
{

}

