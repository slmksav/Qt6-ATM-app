#include "sessiondata.h"
#include <QDebug>

SessionData::SessionData()
{
    //start timer to track inactivity
    connect(&inactivity, SIGNAL(timeout()),
            this, SLOT(handleTimeout()));
    inactivity.start(30000);
}

SessionData::~SessionData()
{
    qDebug() << Q_FUNC_INFO << "Session has ended";
}

void SessionData::resetTimer()
{
    qDebug() << Q_FUNC_INFO << "Inactivity timer was reset";
    inactivity.start();
}

void SessionData::debugPrintData()
{
    qDebug() << Q_FUNC_INFO << "cardID:" << cardID;
    qDebug() << Q_FUNC_INFO << "customerID:" << customerID;
    qDebug() << Q_FUNC_INFO << "accountID" << accountID;
    qDebug() << Q_FUNC_INFO << "accountType" << accountType;
    qDebug() << Q_FUNC_INFO << "customerName" << customerName;

    qDebug() << Q_FUNC_INFO << "accountBalance" << accountBalance;
    qDebug() << Q_FUNC_INFO << "accountCredit" << accountCredit;

    qDebug() << Q_FUNC_INFO << "withdrawMode" << withdrawMode;
    qDebug() << Q_FUNC_INFO << "withdrawAmount" << withdrawAmount;

    int accoundListSize = additionalAccountIDs.count();
    for (int i = 0; i < accoundListSize; ++i) {
        qDebug() << Q_FUNC_INFO << i << "additionalAccountID:" << additionalAccountIDs[i] <<
                    "| additionalAccountName:" << additionalAccountNames[i];
    }

    int transactionListSize = transactionIDs.count();
    for (int i = 0; i < transactionListSize; ++i) {
        qDebug() << Q_FUNC_INFO << i << "transactionIDs:" << transactionIDs[i] <<
                    "| transactionDates:" << transactionDates[i] <<
                    "| transactionAmounts:" << transactionAmounts[i];
    }
}

void SessionData::handleTimeout()
{
    qDebug() << Q_FUNC_INFO << "Inactivity timer ran out";
    emit sendTimeout();
}
