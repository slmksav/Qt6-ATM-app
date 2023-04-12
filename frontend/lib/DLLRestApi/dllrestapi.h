#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H

#include "DLLRestApi_global.h"

#include <QObject>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class DLLRESTAPI_EXPORT DLLRestApi : public QObject
{
    Q_OBJECT

public:
    DLLRestApi();
    virtual ~DLLRestApi();

    static QString getBaseUrl();
    void getCardId(QString hexa);
    void getAccountId(int cardID);
    void getCustomerId(int accountID);
    void getAccountType(int accountID);
    void getCustomerName(int customerID);
    void getAccountBalance(int accountID);
    void getAccountCredit(int accountID);
    void setAccountBalance(int accountID, int withdrawAmount, QString withdrawType);

private slots:

private:
    QString username;
    QString token;
    int accountIDFetchedByCard;
    int debitSaldoonTehtäväMuutos = 1;
    int creditSaldoonTehtäväMuutos = 1;

};

#endif // DLLRESTAPI_H
