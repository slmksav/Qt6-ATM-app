#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include "dllserialport.h"
#include "dllrestapi.h"
#include "dllpincode.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_serialPort = new DLLSerialPort(this);
    m_DLLPinCode = new DLLPinCode(this);
    // Numeroikaa connectionit, jotta voidaan refrensoida niihin dokumentaatiossa.
    connect(m_serialPort, &DLLSerialPort::dataReceived, this, &MainWindow::handleSerialDataReceived); //1. signaali
    connect(this, &MainWindow::cardHexCodeUpdated, m_DLLPinCode, &DLLPinCode::handleCardHexCodeReceived); //2. signaali

    connect(this, SIGNAL(leikkiHexaSignaali(QString)),
            this, SLOT(leikkiHexaSlotti(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getBaseUrl()
{
    return "https://bankdb-r18.onrender.com";
}

void MainWindow::getCustomerData()
{
    QString site_url = MainWindow::getBaseUrl() + "/customer/1";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray authHeader = QString("Bearer %1").arg(token).toLatin1();
    request.setRawHeader("Authorization", authHeader);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {

        if (reply->error()) {
            qDebug() << reply->errorString();
        }
        else {
            QByteArray response = reply->readAll();
            qDebug() << "Raw response:" << response;
            QJsonDocument document = QJsonDocument::fromJson(response);
            QJsonObject object = document.object();
            QString firstName = object.value("first_name").toString();
            QString lastName = object.value("last_name").toString();
            ui->firstName->setText(firstName);
            ui->lastName->setText(lastName);
        }
        reply->deleteLater();
    });

    manager->get(request);
}

//nappi ylläolevaan
void MainWindow::on_customerButton_clicked()
{
    getCustomerData();

}

void MainWindow::getCardhexcodeFromDb()
{
    QString site_url = MainWindow::getBaseUrl() + "/card/2";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray authHeader = QString("Bearer %1").arg(token).toLatin1();
    request.setRawHeader("Authorization", authHeader);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {

        if (reply->error()) {
            qDebug() << reply->errorString();
        }
        else {
            QByteArray response = reply->readAll();
            qDebug() << "Raw response:" << response;

            QJsonDocument document = QJsonDocument::fromJson(response);
            QJsonObject object = document.object();

            // Check if the response contains the cardhexcode key
            if (!object.contains("cardhexcode")) {
                qDebug() << "Response does not contain cardhexcode";
                return;
            }

            cardhexcodeSQLTest = object.value("cardhexcode").toString();
            ui->cardhexcodeLabel->setText(cardhexcode);
        }
        reply->deleteLater();
    });

    manager->get(request);
}

void MainWindow::on_cardhexcodePushbutton_clicked()
{
    getCardhexcodeFromDb();
    if (cardhexcode == cardhexcodeSQLTest)
    {
        qDebug() << "Sarjaportin cardhexcode on sama kun cardhexcodeSQL.";
    }
}

//tämä funktio emittaa cardhexcoden Mikan DLLpincoden käyttöön
//3.4.2023 Koitan itse tehdä tähän huomenna sellaisen toiminnon että se lähettää myös pin-koodin
//tietokannasta samalla tavalla että voi verrata sitä syötettyyn pin-koodiin.
void MainWindow::handleSerialDataReceived(const QString& data)
{
    qDebug() << "Serial data received:" << data;
    ui->serialDataLabel->setText(data);
    cardhexcode = data;
    emit cardHexCodeUpdated(cardhexcode);
}



void MainWindow::on_buttonTestHexaToDLL_clicked()
{
    qDebug() << "leikkiHexaSignaali lähetetään";
    emit leikkiHexaSignaali("0d0a2d303630303035343246450d0a3e");
}

void MainWindow::leikkiHexaSlotti(QString hexaKoodi)
{
    qDebug() << "leikkiHexaSlotti vastaanotti seuraavaa:" << hexaKoodi;

    mikanDLL = new DLLPinCode(this);
    //voidaan myös antaa constructorissa tyyliin
    //mikanDLL = new DLLPinCode(this, hexaKoodi)
    mikanDLL->cardHexCode = hexaKoodi;

    qDebug() << "DLLPinCode-luokan cardHexCode on nyt:" << mikanDLL->cardHexCode;

    mikanDLL->show();

    //tässä ei kannattaisi enää manipuloida dll:ää, vaan antaa sen hoitaa hommat, mutta testin vuoksi
    mikanDLL->handleCardHexCodeReceived(mikanDLL->cardHexCode);
}

