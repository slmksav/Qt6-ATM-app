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

void SessionData::stopTimer()
{
    qDebug() << Q_FUNC_INFO << "Inactivity timer was stopped";
    inactivity.stop();
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

bool SessionData::checkDataValidity()
{
#define __COLOR_RED qDebug() << "\x1b[1;31m";
#define __COLOR_GREEN qDebug() << "\x1b[1;32m";
#define __COLOR_RESET qDebug() << "\x1b[0;0m";

    __COLOR_RED

    //check basics
    if(cardID <= 0 || accountID <= 0 || customerID <= 0 ||
            (accountType != "debit" && accountType != "credit" && accountType != "dual") ||
            customerName == "\0")
    {
        qDebug() << Q_FUNC_INFO << "error in one of these:\n" <<
                    "\tcardID:" << cardID << "| accountID:" << accountID <<
                    "| customerID:" << customerID << "| accountType:" << accountType <<
                    "| customerName:" << customerName;
        __COLOR_RESET
        return false;
    }

    //check money related
    if(accountType == "debit" || accountType == "dual")
    {
        if(accountBalance < 0.0) {
            qDebug() << Q_FUNC_INFO << "Balance is negative:"
                     << accountBalance;
            __COLOR_RESET
            return false;
        }
    }
    if(accountType == "credit" || accountType == "dual")
    {
        if(accountCredit < 0.0 || accountCreditMax < 0.0) {
            qDebug() << Q_FUNC_INFO << "Credit or max is negative: "
                     << "credit:" << accountCredit << "| max:" << accountCreditMax;
            __COLOR_RESET
            return false;
        }
    }

    //check lists
    if(additionalAccountNames.count() != additionalAccountIDs.count())
    {
        qDebug() << Q_FUNC_INFO << "additionalAccounts counts don't match\n"
                 << "\tnames.count:" << additionalAccountNames.count()
                 << "| ids.counts:" << additionalAccountIDs.count();
        __COLOR_RESET
        return false;
    }
    if(transactionIDs.count() != transactionDates.count() ||
            transactionIDs.count() != transactionAmounts.count())
    {
        qDebug() << Q_FUNC_INFO << "transaction counts don't match\n"
                 << "\tids.count:" << transactionIDs.count()
                 << "| dates.counts:" << transactionDates.count()
                 << "| amounts.counts:" << transactionAmounts.count();
        __COLOR_RESET
        return false;
    }

    __COLOR_GREEN
    qDebug() << Q_FUNC_INFO << "Data seems fine";
    __COLOR_RESET
    return true;
}

void SessionData::handleTimeout()
{
    qDebug() << Q_FUNC_INFO << "Inactivity timer ran out";
    emit sendTimeout();
}
