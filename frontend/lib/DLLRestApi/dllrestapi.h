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

    QString token; //session token

    static QString getBaseUrl();

    bool postLogin(QString hex, QString pin);
    bool postEmail(int accountID, QString log);

    bool sendRequest(const QJsonObject& jsonObj, const QString& endpoint);

    int getCardId(QString hexa);
    int getAccountId(int cardID);
    int getCustomerId(int accountID);
    QString getAccountType(int accountID);
    QString getCustomerName(int customerID);
    double getAccountBalance(int accountID);
    double getAccountCredit(int accountID);
    double getCreditMax(int accountID);

    QList<int> getAdditionalAccountIDs(int cardID);
    QList<QString> getAdditionalAccountNames(int cardID);

    QList<int> getTransactionIDs(int accountID);
    QList<QString> getTransactionDates(int accountID);
    QList<double> getTransactionAmounts(int accountID);

    void setAccountBalance(int accountID, int withdrawAmount, QString withdrawType);
signals:
    void withdrawalSuccess(bool);
private slots:

private:
    QNetworkReply *reply;
    QByteArray response_data;
    QString username;

    int accountIDFetchedByCard;

    QJsonDocument doUrlGetQuery(QString site_url);
};

#endif // DLLRESTAPI_H
