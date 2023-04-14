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
    int getCardId(QString hexa);
    int getAccountId(int cardID);
    int getCustomerId(int accountID);
    QString getAccountType(int accountID);
    QString getCustomerName(int customerID);
    double getAccountBalance(int accountID);
    double getAccountCredit(int accountID);

    QList<int> getAdditionalAccountIDs(int cardID);
    QList<QString> getAdditionalAccountNames(int cardID);

    void setAccountBalance(int accountID, int withdrawAmount, QString withdrawType);
signals:
    void withdrawalSuccess(bool);
private slots:

private:
    QNetworkReply *reply;
    QByteArray response_data;
    QString username;
    QString token;
    int accountIDFetchedByCard;
};

#endif // DLLRESTAPI_H
