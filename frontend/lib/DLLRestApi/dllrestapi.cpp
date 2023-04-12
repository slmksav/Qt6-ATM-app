#include "dllrestapi.h"

DLLRestApi::DLLRestApi()
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

    QUrlQuery query;
    query.addQueryItem("id", "1");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        int idaccount = object.value("idaccount").toInt();

        qDebug() << "idaccount: " << idaccount;
        return idaccount;
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
        return -1;
    }

    networkReply->deleteLater();
    return -1;
}

QString DLLRestApi::getAccountType(int accountID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(accountID);

    QUrlQuery query;
    query.addQueryItem("id", "1");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();

        QString accountType = object.value("accountType").toString();
        bool creditSaldoIsNull = object.value("creditSaldo").isNull();
        bool debitSaldoIsNull = object.value("debitSaldo").isNull();

        qDebug() << "accountType: " << accountType;
        qDebug() << "creditSaldo is null: " << creditSaldoIsNull;
        qDebug() << "debitSaldo is null: " << debitSaldoIsNull;

        networkReply->deleteLater();

        return accountType;
    }
    else {
        QString errorMessage = "Network error: " + networkReply->errorString();
        networkReply->deleteLater();
        return errorMessage;
    }
}




double DLLRestApi::getAccountBalance(int accountID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(accountID);

    QUrlQuery query;
    query.addQueryItem("id", "1");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    double saldo = 0.0;

    if(networkReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();

        saldo = object.value("debitSaldo").toDouble();

        networkReply->deleteLater();
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
        networkReply->deleteLater();
    }

    return saldo;
}


double DLLRestApi::getAccountCredit(int accountID)
{
    QString url = getBaseUrl() + "/account/" + QString::number(accountID);

    QUrlQuery query;
    query.addQueryItem("id", "1");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    double creditSaldo = 0.0;

    if(networkReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();

        QString creditSaldoString = object.value("creditSaldo").toString();
        creditSaldo = creditSaldoString.toDouble();

        networkReply->deleteLater();
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
        networkReply->deleteLater();
        return -1.0;
    }

    return creditSaldo;
}

void DLLRestApi::setAccountBalance(int accountID, int withdrawAmount, QString withdrawType)
{
    if (withdrawType == debit) {
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
    QString url = getBaseUrl() + "/customer/" + QString::number(accountID);

    QUrlQuery query;
    query.addQueryItem("id", "1");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QByteArray responseData;

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        qDebug() << "Response JSON:" << object;

        QString idcustomer = QString::number(object.value("idcustomer").toInt());
        qDebug() << "idcustomer: " << idcustomer;

        return idcustomer.toInt();
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
        return -1;
    }

    networkReply->deleteLater();
    return -1;
}

QString DLLRestApi::getCustomerName(int customerID)
{
    QString url = getBaseUrl() + "/customer/" + QString::number(customerID);

    QUrlQuery query;
    query.addQueryItem("id", "1");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();

        QString firstName = object.value("first_name").toString();
        QString lastName = object.value("last_name").toString();

        QString fullName = firstName + " " + lastName;

        networkReply->deleteLater();

        return fullName;
    }
    else {
            QString errorMessage = "Network error: " + networkReply->errorString();
            networkReply->deleteLater();
            return errorMessage;
        }
}

////////// Loppuuu ////////////////////////
/// //////////////////////////////////////




