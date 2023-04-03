#include "dllrestapi.h"

DLLRestApi::DLLRestApi()
{

}

QString DLLRestApi::getBaseUrl()
{
     return "https://bankdb-r18.onrender.com";
}

void DLLRestApi::getAccount2Data(QString samuliAccount)  // samulin tili
{
    QString url = getBaseUrl() + "/account/" + samuliAccount;

    QUrlQuery query;
    query.addQueryItem("id", "2");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QByteArray responseData;

    while(!networkReply->isFinished()) {
        qApp->processEvents();
    }

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        QString debitSaldo = object.value("debitSaldo").toString();
        QString accNumDebit = object.value("accNumDebit").toString();

        qDebug() << "debitSaldo: " << debitSaldo;
        qDebug() << "accNumDebit: " << accNumDebit;
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}


/*void MainWindow::on_customerButton_clicked()
{
    DLLRestApi restApi;
    restApi.getAccount2Data("2");

}*/

void DLLRestApi::getCard2Data(QString samuliCard)  // samulin kortti
{
    QString url = getBaseUrl() + "/card/" + samuliCard;

    QUrlQuery query;
    query.addQueryItem("id", "2");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QByteArray responseData;

    while(!networkReply->isFinished()) {
        qApp->processEvents();
    }

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        QString fourdigitpin = object.value("fourdigitpin").toString();
        QString cardhexcode = object.value("cardhexcode").toString();

        qDebug() << "fourdigitpin: " << fourdigitpin;
        qDebug() << "cardhexcode: " << cardhexcode;
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}

void DLLRestApi::getCustomerData(QString sauliCustomer)  // saulin käyttäjä
{
    QString url = getBaseUrl() + "/customer/" + sauliCustomer;

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

    while(!networkReply->isFinished()) {
        qApp->processEvents();
    }

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        QString debitSaldo = object.value("debitSaldo").toString();
        QString accNumDebit = object.value("accNumDebit").toString();

        qDebug() << "debitSaldo: " << debitSaldo;
        qDebug() << "accNumDebit: " << accNumDebit;
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}

void DLLRestApi::getCustomer2Data(QString samuliCustomer)  // Samuli Käyttäjä
{
    QString url = getBaseUrl() + "/customer/" + samuliCustomer;

    QUrlQuery query;
    query.addQueryItem("id", "2");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QByteArray responseData;

    while(!networkReply->isFinished()) {
        qApp->processEvents();
    }

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        QString debitSaldo = object.value("debitSaldo").toString();
        QString accNumDebit = object.value("accNumDebit").toString();

        qDebug() << "debitSaldo: " << debitSaldo;
        qDebug() << "accNumDebit: " << accNumDebit;
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}

