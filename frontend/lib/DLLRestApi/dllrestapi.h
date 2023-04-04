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
    void getCard2Data(QString samuliCard);        // Samulin Kortti
    void getCustomerData(QString sauliCustomer);    //SAULIN käyttäjä
    void getCustomer2Data(QString samuliCustomer);    //Samulin Käyttäjä
private slots:

private:
    QNetworkReply *reply;
    QByteArray response_data;
    QString username;
    QString token;

};

#endif // DLLRESTAPI_H
