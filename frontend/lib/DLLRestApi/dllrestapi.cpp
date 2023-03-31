#include "dllrestapi.h"

DLLRestApi::DLLRestApi()
{

}

QString DLLRestApi::getBaseUrl()
{
    return "http://localhost:3000";
}

void DLLRestApi::getCustomerData()
{
    QString site_url = DLLRestApi::getBaseUrl() + "/customer/";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

void DLLRestApi::getLoginData()
{
    QString site_url = DLLRestApi::getBaseUrl() + "/login/";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

void DLLRestApi::getCardData()
{
QString site_url = DLLRestApi::getBaseUrl() + "/card/";
QNetworkRequest request((site_url));
request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

// Define the MySQL connection parameters
    QString password = "test";
    QString database = "bankdb";

    // Connect to the database
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(password);
    db.setDatabaseName(database);
    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        return;
    }

    // Execute a SELECT query to retrieve data from the "card" table
    QSqlQuery query;
    if (!query.exec("SELECT * FROM card")) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        db.close();
        return;
    }

    // Retrieve and print the data from the query result
    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        int value = query.value("value").toInt();
        qDebug() << "ID:" << id << "Name:" << name << "Value:" << value;
    }

    // Close the database connection
    db.close();
}

