#include "sessiondata.h"
#include <QDebug>

SessionData::SessionData()
{
//    //call data from database
//    cardID = getCardID();
//    accountID = getAccountID();
//    accountType = getAccountType();
//    customerName = getCustomerName();

//    accountBalance = getAccountBalance();
//    accountCredit = getAccountCredit();

    //start timer to track inactivity
    connect(&inactivity, SIGNAL(timeout()),
            this, SLOT(handleTimeout()));
    inactivity.start(5000);
}

SessionData::~SessionData()
{
    qDebug() << "Session has ended";
}

void SessionData::resetTimer()
{
    qDebug() << "Inactivity timer was reset";
    inactivity.start();
}

void SessionData::handleTimeout()
{
    qDebug() << "Inactivity timer ran out";
    emit sendTimeout();
}
