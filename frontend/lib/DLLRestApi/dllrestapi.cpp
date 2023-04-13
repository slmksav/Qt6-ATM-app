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

int DLLRestApi::getAccountId(int cardID)
{
    QString site_url = DLLRestApi::getBaseUrl() + "/getAccountID/withcardID/" + QString::number(cardID);

    QUrlQuery query;
    query.addQueryItem("id", QString::number(cardID));

    QUrl urlWithQuery(site_url);
    urlWithQuery.setQuery(query);
    qDebug() << Q_FUNC_INFO << site_url;

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
    query.addQueryItem("id", QString::number(accountID));

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);
    qDebug() << Q_FUNC_INFO << url;

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

        bool accNumCredit = object.value("accNumCredit").isNull();
        bool accNumDebit = object.value("accNumDebit").isNull();

        QString accountType;
        if (accNumCredit && !accNumDebit) {
            accountType = "Debit";
        } else if (!accNumCredit && accNumDebit) {
            accountType = "Credit";
        } else if (!accNumCredit && !accNumDebit) {
            accountType = "Dual";
        } else {
            accountType = "Unknown";
        }

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
    query.addQueryItem("id", QString::number(accountID));

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);
    qDebug() << Q_FUNC_INFO << url;

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
    query.addQueryItem("id", QString::number(accountID));

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);
    qDebug() << Q_FUNC_INFO << url;

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

int DLLRestApi::getCustomerId(int accountID)
{
    QString url = getBaseUrl() + "/customer/" + QString::number(accountID);

    QUrlQuery query;
    query.addQueryItem("id", QString::number(accountID));

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);
    qDebug() << Q_FUNC_INFO << url;

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
    query.addQueryItem("id", QString::number(customerID));

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);
    qDebug() << Q_FUNC_INFO << url;

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

//TÄSTÄ ALKAA SETIT. NÄMÄ PITÄÄ TEHDÄ CONNECT NETWORK MANAGER TYYPPISESTI
void DLLRestApi::setAccountBalance(int accountID, int withdrawAmount, QString withdrawType)
{
    double accountBalance = 0.0;
    QString site_url = DLLRestApi::getBaseUrl() + "/account/" + QString::number(accountID);
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray authHeader = QString("Bearer %1").arg(token).toLatin1();
    request.setRawHeader("Authorization", authHeader);
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    connect(manager, &QNetworkAccessManager::finished, [=, &accountBalance](QNetworkReply *reply) {
        if (reply->error()) {
            // Handle the error
        } else {
            QByteArray response = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
            QJsonObject jsonObject = jsonResponse.object();
            accountBalance = jsonObject["balance"].toDouble();
        }
        reply->deleteLater();
    });
    manager->get(request);

    QEventLoop loop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (withdrawType == "debit" && accountBalance < (double)withdrawAmount) {
        double newBalance = accountBalance - withdrawAmount;

        QJsonObject requestBody;
        requestBody["balance"] = newBalance;
        QJsonDocument requestBodyDoc(requestBody);
        QByteArray requestBodyData = requestBodyDoc.toJson();
        site_url = DLLRestApi::getBaseUrl() + "/account/" + QString::number(accountID);
        request.setUrl(site_url);
        manager->put(request, requestBodyData);
        emit withdrawalSuccess(true);
    } else if (withdrawType == "credit" && accountBalance < (double)withdrawAmount) {
        double newBalance = accountBalance + withdrawAmount;

        QJsonObject requestBody;
        requestBody["balance"] = newBalance;
        QJsonDocument requestBodyDoc(requestBody);
        QByteArray requestBodyData = requestBodyDoc.toJson();
        site_url = DLLRestApi::getBaseUrl() + "/account/" + QString::number(accountID);
        request.setUrl(site_url);
        manager->put(request, requestBodyData);
        emit withdrawalSuccess(true);
    } else {
        // Invalid withdrawal!
        qDebug() << "Withdrawal failure!";
        emit withdrawalSuccess(false);
    }
}
