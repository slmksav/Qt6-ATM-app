#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>


#include "DLLRestApi_global.h"

class DLLRESTAPI_EXPORT DLLRestApi
{
public:
    DLLRestApi();
    QNetworkAccessManager *getManager;
    static QString getBaseUrl();
    int getCardId(QString hexa);
    int getAccountId(int cardID);
    int getCustomerId(int accountID);
    QString getAccountType(int accountID);
    QString getCustomerName(int customerID);
    double getAccountBalance(int accountID);
    double getAccountCredit(int accountID);

private slots:

private:
    QNetworkReply *reply;
    QByteArray response_data;
    QString username;
    QString token;

};

#endif // DLLRESTAPI_H
