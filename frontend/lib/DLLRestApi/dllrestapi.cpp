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
    //return "http://localhost:3000";
}

bool DLLRestApi::postLogin(QString hex, QString pin)
{
    QJsonObject jsonObj;
    jsonObj.insert("username", hex);
    jsonObj.insert("password", pin);

    QString site_url = getBaseUrl() + "/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager * loginManager = new QNetworkAccessManager(this);

    QNetworkReply* networkReply = loginManager->post(request, QJsonDocument(jsonObj).toJson());

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << Q_FUNC_INFO << "Raw response:" << responseData;

        token = QString(responseData);

        if(token == "false")
            return false;

        return true;
    }
    else {
        qDebug() << Q_FUNC_INFO<< "Network error: " << networkReply->errorString();
        return false;
    }
}

int DLLRestApi::getAccountId(int cardID)
{
    QString site_url = DLLRestApi::getBaseUrl() + "/getAccountID/withcardID/" + QString::number(cardID);

    QUrlQuery query;
    query.addQueryItem("cardID", QString::number(cardID));

    QUrl urlWithQuery(site_url);
    urlWithQuery.setQuery(query);
    qDebug() << Q_FUNC_INFO << "Täällä haetaan getAccountID:n avulla accountID" << site_url;

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
        int idaccount = object.value("id_account").toInt();

        qDebug() << "idaccount (haettu cardID avulla): " << idaccount;
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
            accountType = "debit";
        } else if (!accNumCredit && accNumDebit) {
            accountType = "credit";
        } else if (!accNumCredit && !accNumDebit) {
            accountType = "dual";
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
        qDebug() << "JSON object: (getAccountBalancessa)" << object; // Print the JSON object

        QJsonValue saldoValue = object.value("debitSaldo");
        QString saldoFetched = saldoValue.toString();
        qDebug() << "saldoFetched (Qstring ennen double conversiota" << saldoFetched;
        if (saldoFetched.isNull()) {
            qDebug() << "Error: debitSaldo value is null";
        } else {
            saldo = saldoFetched.toDouble();
            qDebug() << Q_FUNC_INFO << "Debit saldo for account " << accountID << " is " << saldo;
        }
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
        qDebug() << "JSON object: (getAccountBalancessa)" << object; // Print the JSON object

        QJsonValue creditSaldoValue = object.value("creditSaldo");
        QString creditSaldoFetched = creditSaldoValue.toString();
        qDebug() << "saldoFetched (Qstring ennen double conversiota" << creditSaldoFetched;
        if (creditSaldoFetched.isNull()) {
            qDebug() << "Error: debitSaldo value is null";
        } else {
            creditSaldo = creditSaldoFetched.toDouble();
            qDebug() << Q_FUNC_INFO << "Debit saldo for account " << accountID << " is " << creditSaldo;
        }
        networkReply->deleteLater();
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
        networkReply->deleteLater();
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

double DLLRestApi::getCreditMax(int accountID) //HUOM. luotto on siis tilikohtainen, ei korttikohtainen.
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

    double creditMax = 0.0;

    if(networkReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = networkReply->readAll();
        qDebug() << "Raw response:" << responseData;

        QJsonDocument document = QJsonDocument::fromJson(responseData);
        QJsonObject object = document.object();
        qDebug() << "JSON object: (getCreditMax)" << object; // Print the JSON object

        QJsonValue creditMaxValue = object.value("creditMax");
        QString creditMaxFetched = creditMaxValue.toString();
        qDebug() << "creditMax: (Qstring ennen double conversiota" << creditMaxFetched;
        if (creditMaxFetched.isNull()) {
            qDebug() << "Error: credit value is null!";
        } else {
            creditMax = creditMaxFetched.toDouble();
            qDebug() << Q_FUNC_INFO << "Maximum credit is" << creditMax << "for account:" << accountID;
        }
        networkReply->deleteLater();
    }
    else {
        qDebug() << "Network error fetching max credit: " << networkReply->errorString();
        networkReply->deleteLater();
        return -1;
    }
    return creditMax;
}

//TÄSTÄ ALKAA LISTOJA PALAUTTAVAT FUNKTIOT
QJsonDocument DLLRestApi::doUrlGetQuery(QString site_url)
{
    qDebug() << Q_FUNC_INFO << "requesting with url:" << site_url;

    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("token"), QByteArray(token.toUtf8()));

    QNetworkAccessManager networkManager;
    QNetworkReply* networkReply = networkManager.get(request);

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << Q_FUNC_INFO << "Raw response:" << responseData;
        QJsonDocument document = QJsonDocument::fromJson(responseData);

        return document;
    }
    else {
        qDebug() << Q_FUNC_INFO << "Network error: " << networkReply->errorString();
        QJsonDocument document;

        return document;
    }
}

QList<int> DLLRestApi::getAdditionalAccountIDs(int cardID)
{
    QString site_url = DLLRestApi::getBaseUrl() + "/additionals/ids/" + QString::number(cardID);

    QJsonDocument document = doUrlGetQuery(site_url);

    if(document.isNull())
    {
        QList<int> err{};
        return err;
    }

    QJsonArray idArr = document.array();

    qDebug() << Q_FUNC_INFO << "QJsonArray size:" << idArr.count();

    QList<int> accounts{};
    for (int i = 0; i < idArr.count(); ++i) {
        QJsonObject object = idArr[i].toObject();
        accounts.append(object.value("idaccount").toInt());
    }

    qDebug() << Q_FUNC_INFO << "list size:" << accounts.count();

    return accounts;
}

QList<QString> DLLRestApi::getAdditionalAccountNames(int cardID)
{
    QString site_url = DLLRestApi::getBaseUrl() + "/additionals/names/" + QString::number(cardID);

    QJsonDocument document = doUrlGetQuery(site_url);

    if(document.isNull())
    {
        QList<QString> err{};
        return err;
    }
    QJsonArray nameArr = document.array();

    site_url = DLLRestApi::getBaseUrl() + "/additionals/types/" + QString::number(cardID);

    document = doUrlGetQuery(site_url);

    if(document.isNull())
    {
        QList<QString> err{};
        return err;
    }
    QJsonArray typeArr = document.array();

    qDebug() << Q_FUNC_INFO << "nameArr size:" << nameArr.count() <<
                "| typeArr size:" << typeArr.count();

    QList<QString> accounts{};
    for (int i = 0; i < nameArr.count(); ++i) {
        QJsonObject name = nameArr[i].toObject();
        QJsonObject type = typeArr[i].toObject();

        bool accNumCredit = type.value("accNumCredit").isNull();
        bool accNumDebit = type.value("accNumDebit").isNull();

        QString accountType;
        if (accNumCredit && !accNumDebit) {
            accountType = "debit";
        } else if (!accNumCredit && accNumDebit) {
            accountType = "credit";
        } else if (!accNumCredit && !accNumDebit) {
            accountType = "dual";
        } else {
            accountType = "Unknown";
        }

        accounts.append(name.value("first_name").toString() + " " +
                        name.value("last_name").toString() + " - " +
                        accountType);
    }

    qDebug() << Q_FUNC_INFO << "list size:" << accounts.count();

    return accounts;
}

QList<int> DLLRestApi::getTransactionIDs(int accountID)
{
    QString site_url = DLLRestApi::getBaseUrl() + "/transactionHistory/ids/" + QString::number(accountID);

    QJsonDocument document = doUrlGetQuery(site_url);

    if(document.isNull())
    {
        QList<int> err{};
        return err;
    }

    QJsonArray idArr = document.array();

    qDebug() << Q_FUNC_INFO << "QJsonArray size:" << idArr.count();

    QList<int> transactions{};
    for (int i = 0; i < idArr.count(); ++i) {
        QJsonObject object = idArr[i].toObject();
        transactions.append(object.value("idtransactions").toInt());
    }

    qDebug() << Q_FUNC_INFO << "list size:" << transactions.count();

    return transactions;
}

QList<QString> DLLRestApi::getTransactionDates(int accountID)
{
    QString site_url = DLLRestApi::getBaseUrl() + "/transactionHistory/dates/" + QString::number(accountID);

    QJsonDocument document = doUrlGetQuery(site_url);

    if(document.isNull())
    {
        QList<QString> err{};
        return err;
    }

    QJsonArray datesArr = document.array();

    qDebug() << Q_FUNC_INFO << "QJsonArray size:" << datesArr.count();

    QList<QString> transactions{};
    for (int i = 0; i < datesArr.count(); ++i) {
        QJsonObject object = datesArr[i].toObject();
        transactions.append(object.value("date_transactions").toString());
    }

    qDebug() << Q_FUNC_INFO << "list size:" << transactions.count();

    return transactions;
}

QList<double> DLLRestApi::getTransactionAmounts(int accountID)
{
    QString site_url = DLLRestApi::getBaseUrl() + "/transactionHistory/amounts/" + QString::number(accountID);

    QJsonDocument document = doUrlGetQuery(site_url);

    if(document.isNull())
    {
        QList<double> err{};
        return err;
    }

    QJsonArray amountsArr = document.array();

    qDebug() << Q_FUNC_INFO << "QJsonArray size:" << amountsArr.count();

    QList<double> transactions{};
    for (int i = 0; i < amountsArr.count(); ++i) {
        QJsonObject object = amountsArr[i].toObject();
        QString amountStr = object.value("amount").toString();
        transactions.append(amountStr.toDouble());
    }

    qDebug() << Q_FUNC_INFO << "list size:" << transactions.count();

    return transactions;
}

//TÄSTÄ ALKAA SETIT. NÄMÄ PITÄÄ TEHDÄ CONNECT NETWORK MANAGER TYYPPISESTI
void DLLRestApi::setAccountBalance(int accountID, int withdrawAmount, QString withdrawType)
{
    double currentBalance = 0.0; //voi olla joko creditsaldo tai debitsaldo edempänä
    double creditMax = 0.0; //ei jäsenmuuttuja! (sellaista ei ole)
    bool debitMode = false;
    if(withdrawType == "debit") {
        debitMode = true;
        currentBalance = getAccountBalance(accountID);
    }
    else {
        debitMode = false;
        creditMax = getCreditMax(accountID);
        currentBalance = getAccountCredit(accountID);
    }

    if(debitMode == true) {
        if(currentBalance - (double)withdrawAmount < 0)
        {
            qDebug() << Q_FUNC_INFO << "currentBalance - (double)withdrawAmount < 0\n" <<
                        currentBalance << " - " << (double)withdrawAmount;
            emit withdrawalSuccess(false);
            return;
        }
    }
    else {
        if((currentBalance+(double)withdrawAmount) > creditMax)
        {
            qDebug() << Q_FUNC_INFO << "currentBalance - (double)withdrawAmount < 0\n" <<
                        currentBalance << " - " << (double)withdrawAmount;
            emit withdrawalSuccess(false);
            return;
        }
    }

    QJsonObject jsonObj;
    jsonObj.insert("id", accountID);
    jsonObj.insert("amount", withdrawAmount);
    jsonObj.insert("type", withdrawType);

    QString site_url = getBaseUrl() + "/account/";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager * loginManager = new QNetworkAccessManager(this);

    QNetworkReply* networkReply = loginManager->put(request, QJsonDocument(jsonObj).toJson());

    QEventLoop loop;
    QObject::connect(networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData;

    if(networkReply->error() == QNetworkReply::NoError) {
        responseData = networkReply->readAll();
        qDebug() << Q_FUNC_INFO << "Raw response:" << responseData;

        if(responseData.toInt() == 0)
        {
            qDebug() << Q_FUNC_INFO << "zero rows affected, failed";
            emit withdrawalSuccess(false);
            return;
        }
        emit withdrawalSuccess(true);
        return;
    }
    else {
        qDebug() << Q_FUNC_INFO<< "Network error: " << networkReply->errorString();
        emit withdrawalSuccess(false);
        return;
    }
}
