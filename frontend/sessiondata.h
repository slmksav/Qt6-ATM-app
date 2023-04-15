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

    int cardID; //getCardID(QString hexa);
    int accountID; //getAccountID(int cardID);
    int customerID; //getCustomerID(int cardID);
    QString accountType; //getAccountType(int accountID);
    QString customerName; //getCustomerName(int customerID);

    double accountBalance; //getAccountBalance(int accountID);
    double accountCredit; //getAccountCredit(int accountID);

    QString withdrawMode;
    int withdrawAmount = 0;

    QList<QString> additionalAccountNames; //getAdditionalAccountNames(int customerID);
    QList<int> additionalAccountIDs; //getAdditionalAccountIDs(int customerID);

    QList<int> transactionIDs; //getTransactionIDs(int accountID);
    QList<QString> transactionDates; //QList<QDate> getTransactionDates(QList<int> transactionIDs);
    QList<double> transactionAmounts; //QList<int> getTransactionAmounts(QList<int> transactionIDs);

    QString language = "fi";

signals:
    void sendTimeout();
    void sendLogout();

public slots:
    void resetTimer();
    void stopTimer();
    void debugPrintData();

private slots:
    void handleTimeout();

private:
    QTimer inactivity;
};

#endif // SESSIONDATA_H
