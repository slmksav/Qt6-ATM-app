#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

#include "DLLRestApi_global.h"

class DLLRESTAPI_EXPORT DLLRestApi
{
public:
    DLLRestApi();
    static QString getBaseUrl();

private slots:
    void getCustomerData();
    void getLoginData();
    void getCardData();
    void getAccountData();
    void getTransactions();
private:
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // DLLRESTAPI_H
