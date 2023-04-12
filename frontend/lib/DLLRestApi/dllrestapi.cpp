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

void DLLRestApi::getAccountId(int cardID)
{
    QString site_url = DLLRestApi::getBaseUrl() + "/getAccountID/withcardID/" + QString::number(cardID);
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray authHeader = QString("Bearer %1").arg(token).toLatin1();
    request.setRawHeader("Authorization", authHeader);
    QUrl url = request.url();
    qDebug() << "getAccountID pyynnön url:" << url.toString();
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, [=](QNetworkReply *reply) {
        if (reply->error()) {
            qDebug() << reply->errorString();
        }
        else {
            QByteArray response = reply->readAll();
            QJsonDocument document = QJsonDocument::fromJson(response);
            QJsonObject object = document.object();
            qDebug() << "Response (pitäisi tulla raw response)" << response;
            if (!object.contains("idcard")) {
                qDebug() << "idcard not found";
            } else {
                accountIDFetchedByCard = object.value("id_account").toInt();
                qDebug() << "Account ID: " << accountIDFetchedByCard << "fetched with cardID: " << cardID;
            }
        }
        reply->deleteLater();
    });
    manager->get(request);
}


void DLLRestApi::getAccountType(int accountID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(accountID);

}

void DLLRestApi::getAccountBalance(int accountID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(accountID);

}

void DLLRestApi::getAccountCredit(int accountID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(accountID);

}

void DLLRestApi::setAccountBalance(int accountID, int withdrawAmount, QString withdrawType)
{
    //Jos kyse on debit-nostosta
    if (withdrawType == "debit") {

    }
    //Jos kyse on credit-nostosta
    else {

    }
}

void DLLRestApi::getCustomerId(int accountID)
{


}

void DLLRestApi::getCustomerName(int customerID)
{
    QString url = getBaseUrl() + "/customer/" + QString::number(customerID);

}
