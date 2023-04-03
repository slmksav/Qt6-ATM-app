#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include "dllrestapi.h"
#include "codeui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_serialPort = new DLLSerialPort(this);
    connect(m_serialPort, &DLLSerialPort::dataReceived, this, &MainWindow::handleSerialDataReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getBaseUrl()
{
    return "https://bankdb-r18.onrender.com";
    //tarvittaessa helppo muuttaa
    //esimerkiksi
    //return "https://azure.com/myapp"; Tämä pitäisi saada muutettua johonkin ulkoiseen palvelimeen, koska yhteys db4free:stä tähän on nyt lokaali
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

    // Get list of available serial ports
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    // Loop over ports and print information
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        qDebug() << "\n"
                 << "Port:" << portInfo.portName() << "\n"
                 << "Location:" << portInfo.systemLocation() << "\n"
                 << "Description:" << portInfo.description() << "\n"
                 << "Manufacturer:" << portInfo.manufacturer() << "\n"
                 << "Serial number:" << portInfo.serialNumber() << "\n"
                 << "Vendor Identifier:"
                 << (portInfo.hasVendorIdentifier()
                     ? QByteArray::number(portInfo.vendorIdentifier(), 16)
                     : QByteArray()) << "\n"
                 << "Product Identifier:"
                 << (portInfo.hasProductIdentifier()
                     ? QByteArray::number(portInfo.productIdentifier(), 16)
                     : QByteArray());
    }

}

void MainWindow::handleSerialDataReceived(const QString& data)
{
    qDebug() << "Serial data received:" << data;
    ui->serialDataLabel->setText(data);
}
