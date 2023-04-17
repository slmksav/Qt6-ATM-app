#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include "dllrestapi.h"

#include <QTimer>
#include <QObject>
#include <QList>

class SessionData : public QObject
{
    Q_OBJECT

public:
    explicit SessionData();
    ~SessionData();

    DLLRestApi * restApi;

    //remember who logged in
    int originalAccountID = 0;
    QString originalCustomerName = "\0";

    //the data
    int cardID = 0; //getCardID(QString hexa);
    int accountID = 0; //getAccountID(int cardID);
    int customerID = 0; //getCustomerID(int accountID);
    QString accountType = "\0"; //getAccountType(int accountID);
    QString customerName = "\0"; //getCustomerName(int customerID);

    double accountBalance = -1.0; //getAccountBalance(int accountID);
    double accountCredit = -1.0; //getAccountCredit(int accountID);
    double accountCreditMax = -1.0; //getCreditMax(int accountID);

    QString withdrawMode = "\0";
    int withdrawAmount = 0;

    QList<QString> additionalAccountNames; //getAdditionalAccountNames(int customerID);
    QList<int> additionalAccountIDs; //getAdditionalAccountIDs(int customerID);

    QList<int> transactionIDs; //getTransactionIDs(int accountID);
    QList<QString> transactionDates; //getTransactionDates(int accountID);
    QList<double> transactionAmounts; //getTransactionAmounts(int accountID);

    QString language = "fi";

signals:
    void sendTimeout();
    void sendLogout();

public slots:
    void resetTimer();
    void stopTimer();
    void debugPrintData();
    bool checkDataValidity();

private slots:
    void handleTimeout();

private:
    QTimer inactivity;
};

#endif // SESSIONDATA_H
