#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QTimer>
#include <QObject>
#include <QList>

class SessionData : public QObject
{
    Q_OBJECT

public:
    explicit SessionData();
    ~SessionData();

    int cardID; //getCardID(QString hexa);
    int accountID; //getAccountID(int cardID);
    int customerID; //getCustomerID(int cardID);
    QString accountType; //getAccountType(int accountID);
    QString customerName; //getCustomerName(int customerID);

    double accountBalance; //getAccountBalance(int accountID);
    double accountCredit; //getAccountCredit(int accountID);

    QString withdrawMode;
    int withdrawAmount;

    QList<QString> additionalAccountNames; //getAdditionalAccountNames(int customerID);
    QList<int> additionalAccountIDs; //getAdditionalAccountIDs(int customerID);

    QList<int> transactionIDs; //getTransactionIDs(int accountID);
    QList<QString> transactionDates; //QList<QDate> getTransactionDates(QList<int> transactionIDs);
    QList<double> transactionAmounts; //QList<int> getTransactionAmounts(QList<int> transactionIDs);

signals:
    void sendTimeout();
    void sendLogout();

public slots:
    void resetTimer();

private slots:
    void handleTimeout();

private:
    QTimer inactivity;
};

#endif // SESSIONDATA_H
