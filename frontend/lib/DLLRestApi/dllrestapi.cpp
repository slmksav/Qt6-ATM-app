#include "dllrestapi.h"



DLLRestApi::DLLRestApi()
{

}

DLLRestApi::~DLLRestApi()
{

}


QString DLLRestApi::getBaseUrl()
{
     return "https://bankdb-r18.onrender.com";
}



////////// tästä alkaa CARD-funktio///////
////////////////////////////////////////////

int DLLRestApi::getAccountId(int cardID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(cardID);

}

QString DLLRestApi::getAccountType(int accountID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(accountID);

}




double DLLRestApi::getAccountBalance(int accountID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(accountID);

}


double DLLRestApi::getAccountCredit(int accountID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(accountID);

}

void DLLRestApi::setAccountBalance(int accountID, int withdrawAmount, QString withdrawType)
{
    if (withdrawType == "debit") {
        QString site_url = DLLRestApi::getBaseUrl() + "/account/" + QString::number(accountID);;
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray authHeader = QString("Bearer %1").arg(token).toLatin1();
        request.setRawHeader("Authorization", authHeader);
        QJsonObject requestBody;
        requestBody.insert("debitSaldo", debitSaldoonTehtäväMuutos);
        QJsonDocument requestBodyDoc(requestBody);
        QByteArray requestBodyData = requestBodyDoc.toJson();
        QNetworkAccessManager *manager = new QNetworkAccessManager();

        connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << "Debit saldon päivitys ei onnistunut tilille " << accountID;
            }
            else {
                QByteArray response = reply->readAll();
                qDebug() << "Päivitetty debit saldo tilille " << accountID;
            }
            reply->deleteLater();
        });
        manager->put(request, requestBodyData);
    }
    else {
        QString site_url = DLLRestApi::getBaseUrl() + "/account/" + QString::number(accountID);;
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray authHeader = QString("Bearer %1").arg(token).toLatin1();
        request.setRawHeader("Authorization", authHeader);
        QJsonObject requestBody;
        requestBody.insert("creditSaldo", creditSaldoonTehtäväMuutos);
        QJsonDocument requestBodyDoc(requestBody);
        QByteArray requestBodyData = requestBodyDoc.toJson();
        QNetworkAccessManager *manager = new QNetworkAccessManager();

        connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << "Credit saldon päivitys ei onnistunut tilille " << accountID;
            }
            else {
                QByteArray response = reply->readAll();
                qDebug() << "Päivitetty credit saldo tilille " << accountID;
            }
            reply->deleteLater();
        });
        manager->put(request, requestBodyData);
    }
}


////////// tästä alkaa CUSTOMER-funktio///////
////////////////////////////////////////////

int DLLRestApi::getCustomerId(int accountID)
{


}

QString DLLRestApi::getCustomerName(int customerID)
{
    QString url = getBaseUrl() + "/customer/" + QString::number(customerID);

}

////////// Loppuuu ////////////////////////
/// //////////////////////////////////////




