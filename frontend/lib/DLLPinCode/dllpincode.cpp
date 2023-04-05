#include "dllpincode.h"
#include "ui_dllpincode.h"
#include <QSqlQuery>

DLLPinCode::DLLPinCode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLLPinCode)
{
    ui->setupUi(this);
    //cardHexCode = "060006491c";
     ui->labelInterrupt->setVisible(false);
     ui->labelFreezed1->setVisible(false);
     ui->labelFreezed2->setVisible(false);
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

//tämä funktio vastaanottaa cardhexcoden Mikan DLLpincoden käyttöön (kts. DLLPinCode.cpp:n signaalit)
QString DLLPinCode::handleCardHexCodeReceived(QString hexCode)
{
    qDebug()<<"emitattu signaali on " + hexCode;
    cardHexCode = hexCode;
    qDebug()<<"cardHexCode arvo on: " + cardHexCode;
    ui->cardhexcodeLabel->setText(cardHexCode);
    return cardHexCode;
}

void DLLPinCode::getCardInfoFromDb(const QString& cardID)
{
    QString site_url = DLLPinCode::getBaseUrl() + "/card/" + cardID;
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
                    wrongAttempts = object.value("wrongAttemtps").toInt();

                    ui->labelpin->setText(SQLPin);
                    if(wrongAttempts > 0)
                    {
                       ui->labelAttempts->setText(QString::number(wrongAttempts) + " yritystä jäljellä");
                    }
                    else
                    {
                       accountFreezed();
                    }

                }
                reply->deleteLater();
            });

    manager->get(request);
}

//////loppu

void DLLPinCode::enterClickHandler()
{
    timer->stop();
    getCardInfoFromDb(cardID);

    while (cardhexcodeSQL.isEmpty() || SQLPin.isEmpty()) {
        QCoreApplication::processEvents();
    }

    CheckPin = ui->lineEdit->text();
    qDebug() << "Pin joka on syötetty:" << CheckPin;
    qDebug() << "Tietokannasta haettu PIN:" << SQLPin;
    qDebug() << "cardHexCode:" << handleCardHexCodeReceived(cardHexCode);
    qDebug() << "cardhexcodeSQL:" << cardhexcodeSQL;
    if (cardhexcodeSQL == cardHexCode && CheckPin == SQLPin && wrongAttempts > 0)
    {
        emit LoginSuccess(cardID.toInt());
        done(Accepted);


    }
    else
    {
        emit LoginSuccess(0);
        ui->label->setText("Väärin, syötä tunnusluku uudestaan.");
        timer->start(30000);
        wrongAttempts--;
        ui->labelAttempts->setText(QString::number(wrongAttempts) + " yritystä jäljellä");
    }
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
      done(Rejected);
}

void DLLPinCode::accountFreezed()
{
      timer->stop();
      timer->start(5000);
      ui->labelFreezed1->setVisible(true);
      ui->labelFreezed2->setVisible(true);
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
