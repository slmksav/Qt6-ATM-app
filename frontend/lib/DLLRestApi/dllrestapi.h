#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H
#include <QObject>
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
    void getAccount2Data(QString samuliAccount); ;     // Samulin Tili
    void getAccountData(QString sauliAccount); // Saulin tili
    void getCardData(QString sauliCard);    // Saulin Kortti
    void getCard2Data(QString samuliCard);        // Samulin Kortti
    void getCustomerData(QString sauliCustomer);    //SAULIN käyttäjä
    void getCustomer2Data(QString samuliCustomer);    //Samulin Käyttäjä
    void getCardId(QString sauliCard);
    void getAccountId(QString sauliId);
    void getCustomerId(QString sauliId);
    void getAccountType(QString sauliType); //Saulin tilin tyyppi
    void getCustomerName(QString sauliName);
    void getAccountBalance(QString sauliSaldo);
    void getAccountCredit(QString sauliCredit);

private slots:

private:
    QNetworkReply *reply;
    QByteArray response_data;
    QString username;
    QString token;

};

#endif // DLLRESTAPI_H
