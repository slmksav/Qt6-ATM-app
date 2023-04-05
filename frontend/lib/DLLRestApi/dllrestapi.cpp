#include "dllrestapi.h"

DLLRestApi::DLLRestApi()
{

}

QString DLLRestApi::getBaseUrl()
{
     return "https://bankdb-r18.onrender.com";
}

void DLLRestApi::getAccountData(QString sauliAccount) //Saulin tili
{
    QString url = getBaseUrl() + "/account/" + sauliAccount;

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
        QString debitSaldo = object.value("debitSaldo").toString();
        QString accNumDebit = object.value("accNumDebit").toString();
        QString creditMax = object.value("creditMax").toString();

        qDebug() << "debitSaldo: " << debitSaldo;
        qDebug() << "accNumDebit: " << accNumDebit;
        qDebug() << "creditMax: " << creditMax;
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
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

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        QString debitSaldo = object.value("debitSaldo").toString();
        QString accNumDebit = object.value("accNumDebit").toString();
        QString creditMax = object.value("creditMax").toString();

        qDebug() << "debitSaldo: " << debitSaldo;
        qDebug() << "accNumDebit: " << accNumDebit;
        qDebug() << "creditMax: " << creditMax;
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

void DLLRestApi::getCardData(QString sauliCard)//saulin kortti
{
    QString url = getBaseUrl() + "/card/" + sauliCard;

    QUrlQuery query;
    query.addQueryItem("id", "1");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;

    QEventLoop eventLoop; // Create an event loop to block until the request is finished
    QObject::connect(&networkManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

    QNetworkReply* networkReply = networkManager.get(request);

    eventLoop.exec(); // Block until the request is finished

    if(networkReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = networkReply->readAll();
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

void DLLRestApi::getCard2Data(QString samuliCard) { //samulin kortti
    QString url = getBaseUrl() + "/card/" + samuliCard;

    QUrlQuery query;
    query.addQueryItem("id", "2");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;

    QEventLoop eventLoop; // Create an event loop to block until the request is finished
    QObject::connect(&networkManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

    QNetworkReply* networkReply = networkManager.get(request);

    eventLoop.exec(); // Block until the request is finished

    if(networkReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = networkReply->readAll();
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


void DLLRestApi::getCustomerData(QString sauliCustomer)
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

    QEventLoop loop;  // create a QEventLoop
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit())); // connect the signal finished() of networkReply to the slot quit() of the QEventLoop
    loop.exec(); // start the event loop

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        QString firstName = object.value("firstName").toString();
        QString lastName = object.value("lastName").toString();
        QString age = object.value("age").toString();

        qDebug() << "firstName: " << firstName;
        qDebug() << "lastName: " << lastName;
        qDebug() << "age: " << age;
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

    QEventLoop eventLoop;
    QObject::connect(networkReply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if(networkReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        QString first_name = object.value("first_name").toString();
        QString last_name = object.value("last_name").toString();
        QString age = object.value("age").toString();

        qDebug() << "first_name: " << first_name;
        qDebug() << "last_name: " << last_name;
        qDebug() << "age: " << age;

    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}


void DLLRestApi::getCardId(QString sauliCard) //Saulin kortin Hexan haku
{
    QString url = getBaseUrl() + "/card/" + sauliCard;

    QUrlQuery query;
    query.addQueryItem("id", "1");

    QUrl urlWithQuery(url);
    urlWithQuery.setQuery(query);

    QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;

    QEventLoop eventLoop; // Create an event loop to block until the request is finished
    QObject::connect(&networkManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

    QNetworkReply* networkReply = networkManager.get(request);

    eventLoop.exec(); // Block until the request is finished

    if(networkReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        QString cardhexcode = object.value("cardhexcode").toString();

         qDebug() << "cardhexcode: " << cardhexcode;

    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}

void DLLRestApi::getAccountId(QString sauliId) // Saulin Accountin id
{
    QString url = getBaseUrl() + "/account/" + sauliId;

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
        QString idaccount = object.value("idaccount").toString();

        qDebug() << "idaccount: " << idaccount;
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}


void DLLRestApi::getCustomerId(QString sauliId)
{
    QString url = getBaseUrl() + "/customer/" + sauliId;

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

    QEventLoop loop;  // create a QEventLoop
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec(); // start the event loop

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        QString idcustomer = object.value("idcustomer").toString();


        qDebug() << "idcustomer: " << idcustomer;

    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}

void DLLRestApi::getAccountType(QString sauliType)
{
    QString url = getBaseUrl() + "/account/" + sauliType;

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
        QString creditSaldo = object.value("creditSaldo").toString();
        QString debitSaldo = object.value("debitSaldo").toString();
        QString accNumDebit = object.value("accNumDebit").toString();
        QString creditMax = object.value("creditMax").toString();


        qDebug() << "creditSaldo: " << creditSaldo;
        qDebug() << "debitSaldo: " << debitSaldo;
        qDebug() << "accNumDebit: " << accNumDebit;
        qDebug() << "creditMax: " << creditMax;
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}


QJsonObject DLLRestApi::getCustomerName(QString sauliName)
{
    QString url = getBaseUrl() + "/customer/" + sauliName;

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

        QJsonObject result;
        result.insert("first_name", firstName);
        result.insert("last_name", lastName);

        networkReply->deleteLater();

        return result;
    }

    else {
        qDebug() << "Network error: " << networkReply->errorString();
        networkReply->deleteLater();

        // Palauta tyhjä JSON-objekti virheen sattuessa
        return QJsonObject();
    }
}



QJsonObject DLLRestApi::getAccountBalance(QString sauliSaldo)
{
    QString url = getBaseUrl() + "/account/" + sauliSaldo;

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

            QString creditSaldo = object.value("debitSaldo").toString();
            double creditSaldoDouble = creditSaldo.toDouble();

            QJsonObject result;
            result.insert("debitSaldo", creditSaldoDouble);
            networkReply->deleteLater();

            return result;
        }
        else {
            qDebug() << "Network error: " << networkReply->errorString();
            networkReply->deleteLater();

            // Palauta tyhjä JSON-objekti virheen sattuessa
            return QJsonObject();
        }
    }


QJsonObject DLLRestApi::getAccountCredit(QString sauliCredit)
{
    QString url = getBaseUrl() + "/account/" + sauliCredit;

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

        QString creditSaldo = object.value("creditSaldo").toString();
        double creditSaldoDouble = creditSaldo.toDouble();

        QJsonObject result;
        result.insert("creditSaldo", creditSaldoDouble);
        networkReply->deleteLater();

        return result;
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
        networkReply->deleteLater();

        // Palauta tyhjä JSON-objekti virheen sattuessa
        return QJsonObject();
    }
}

