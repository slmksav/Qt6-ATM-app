#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "environment.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getBaseUrl()
{
    return "http://localhost:3000";
    //tarvittaessa helppo muuttaa
    //esimerkiksi
    //return "https://azure.com/myapp";
}


void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    if(QString::compare(response_data,"-4078")==0 || response_data.length()==0){
            ui->mikaInfo->setText("Virhe tietokantayhteydessa");
    }
    else {
    if(QString::compare(response_data, "false")!=0 && response_data.length()>10){
        ui->mikaInfo->setText("Login OK");
        token="Bearer "+response_data;
        qDebug()<<token;
    }
    else{
        ui->mikaInfo->setText("Tunnus ja salasana eivat tasmaa");
        ui->mikaKayttaja->clear();
        ui->mikaSalis->clear();
    }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}


void MainWindow::on_mikaButton_clicked()
{
    username=ui->mikaKayttaja->text();
    QString password=ui->mikaSalis->text();
    QJsonObject jsonObj;
    jsonObj.insert("username",username);
    jsonObj.insert("password",password);

    QString site_url=Environment::getBaseUrl()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

