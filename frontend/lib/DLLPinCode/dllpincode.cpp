#include "dllpincode.h"
#include "ui_dllpincode.h"

DLLPinCode::DLLPinCode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLLPinCode)
{
    ui->setupUi(this);
    //cardHexCode = "060006491c";
     ui->labelInterrupt->setVisible(false);
     ui->lineEdit->setMaxLength(4); // Set the maximum length to 4 digits
     ui->lineEdit->setReadOnly(true); //Cannot write t
     ui->lineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->button1,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->button2,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->button3,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->button4,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->button5,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->button6,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->button7,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->button8,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->button9,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->button0,SIGNAL(clicked()),this,SLOT(numberClickHandler()));
    connect(ui->buttonEnter,SIGNAL(clicked()),this,SLOT(enterClickHandler()));
    connect(ui->ButtonClear,SIGNAL(clicked()),this,SLOT(clearClickHandler()));
    connect(ui->ButtonStop,SIGNAL(clicked()),this,SLOT(stopClickHandler()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(stopClickHandler()));
    timer->start(30000);

}

DLLPinCode::~DLLPinCode()
{
    delete ui;
}

QString DLLPinCode::getBaseUrl()
{
    return "https://bankdb-r18.onrender.com";
}

void DLLPinCode::getCardhexcodeFromDb()
{
    QString site_url = DLLPinCode::getBaseUrl() + "/card/2";
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

                    cardhexcodeSQL = object.value("cardhexcode").toString();
                    SQLPin = object.value("fourdigitpin").toString();
                    ui->labelpin->setText(SQLPin);

                }
                reply->deleteLater();
            });

    manager->get(request);
}
//tämä funktio vastaanottaa cardhexcoden Mikan DLLpincoden käyttöön (kts. DLLPinCode.cpp:n signaalit)
QString DLLPinCode::handleCardHexCodeReceived(QString hexCode)
{
    qDebug()<<"emitattu signaali on " + hexCode;
    cardHexCode = hexCode;
    qDebug()<<"cardHexCode arvo on: " + cardHexCode;
    ui->cardhexcodeLabel->setText(cardHexCode);
    return cardHexCode;
}

void DLLPinCode::numberClickHandler()
{
    QPushButton *numberButton = qobject_cast<QPushButton *>(sender());
        QString clickedValue = numberButton->text();
        timer->stop();
        timer->start(30000);

        InsertingPin += clickedValue;
        ui->lineEdit->setText(InsertingPin);
        CheckPin = clickedValue;

}

void DLLPinCode::enterClickHandler()
{
    timer->stop();
    getCardhexcodeFromDb();

    while (cardhexcodeSQL.isEmpty() || SQLPin.isEmpty()) {
        QCoreApplication::processEvents();
    }

    CheckPin = ui->lineEdit->text();
    qDebug() << "lineEdit content:" << CheckPin;
    qDebug() << "cardHexCode:" << handleCardHexCodeReceived(cardHexCode);
    qDebug() << "cardhexcodeSQL:" << cardhexcodeSQL;
    if (cardhexcodeSQL == cardHexCode && CheckPin == SQLPin)
    {
        ui->labeljee->setText("jeeeeeeeeeeeeeeeeee");
    }
    else
    {
        ui->label->setText("Väärin, syötä tunnusluku uudestaan.");
        timer->start(30000);
    }
}


void DLLPinCode::clearClickHandler()
{
      InsertingPin = "";
      ui->lineEdit->clear();
      timer->stop();
      timer->start(30000);

}

void DLLPinCode::stopClickHandler()
{
      timer->stop();
      timer->start(5000);
      ui->labelInterrupt->setVisible(true);
      ui->label->setVisible(false);
      ui->label_3->setVisible(false);
      ui->labelAttempts->setVisible(false);
      ui->button0->setVisible(false);
      ui->button1->setVisible(false);
      ui->button2->setVisible(false);
      ui->button3->setVisible(false);
      ui->button4->setVisible(false);
      ui->button5->setVisible(false);
      ui->button6->setVisible(false);
      ui->button7->setVisible(false);
      ui->button8->setVisible(false);
      ui->button9->setVisible(false);
      ui->ButtonStop->setVisible(false);
      ui->ButtonClear->setVisible(false);
      ui->buttonEnter->setVisible(false);
      ui->lineEdit->setVisible(false);
}
