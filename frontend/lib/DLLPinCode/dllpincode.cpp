#include "dllpincode.h"
#include "ui_dllpincode.h"

DLLPinCode::DLLPinCode(QWidget *parent, QString cardHexCodeReceived, QString language) :
    QDialog(parent),
    ui(new Ui::DLLPinCode)
{
     ui->setupUi(this);
     languageGlobal = language;
     setLanguage();
     emptyLineEdit();
     ui->labelInterrupt->setVisible(false);
     ui->labelFreezed1->setVisible(false);
     ui->labelFreezed2->setVisible(false);
     ui->labelAttempts->setVisible(false);
     ui->lineEdit->setMaxLength(4);
     ui->lineEdit->setReadOnly(true);
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
    cardHexCode = cardHexCodeReceived;
    qDebug() << "cardHexCode konstruktorissa:" << cardHexCode;
    getWrongAttempts();
    sound();
}

DLLPinCode::~DLLPinCode()
{
    delete ui;
    delete timer;
}

QString DLLPinCode::getBaseUrl()
{
    return "https://bankdb-r18.onrender.com";
}

//tämä funktio hakee cardHexCoden perusteella cardID:n eli rivin primary keyn
int DLLPinCode::getCardIDFromDb()
{
    QString site_url = getBaseUrl() + "/hexcode/hex/" + cardHexCode;
    QUrlQuery query;
    query.addQueryItem("cardID", QString::number(cardID.toInt()));

    QUrl urlWithQuery(site_url);
    urlWithQuery.setQuery(query);
    qDebug() << Q_FUNC_INFO << "Täällä haetaan getCardID:n avulla cardID" << site_url;

                QNetworkRequest request;
    request.setUrl(urlWithQuery);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), QByteArray(token.toUtf8()));

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
        cardID = object.value("idcard").toString();

        qDebug() << "Haettu CardID " << cardID;
        return cardID.toInt();
    }
    else {
        qDebug() << "Network error: " << networkReply->errorString();
        return -1;
    }

    networkReply->deleteLater();
    return -1;
}

//tämä funktio hakee syötetyn hexakoodin perusteella väärien yritysten määrän backendistä
void DLLPinCode::getWrongAttempts()
{
    QString site_url = getBaseUrl() + "/login/" + cardHexCode;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray authHeader = QString("Bearer %1").arg(token).toLatin1();
    request.setRawHeader("Authorization", authHeader);
    QUrl url = request.url();
    qDebug() << "card info URL: " << url.toString();

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
                    wrongAttempts = object.value("wrongAttempts").toInt();
                    if(languageGlobal == "fi" && wrongAttempts < 3)
                    {
                        ui->labelAttempts->setText(QString::number(wrongAttempts) + " yritys(tä) jäljellä!");
                        ui->labelAttempts->setVisible(true);
                    }
                    else if(languageGlobal == "en" && wrongAttempts < 3)
                    {
                        ui->labelAttempts->setText(QString::number(wrongAttempts) + " attempt(s) left!");
                        ui->labelAttempts->setVisible(true);
                    }
                    qDebug() << "wrongAttemptsMäärä" << wrongAttempts;
                    if(wrongAttempts <= 0)
                    {
                        accountFreezed();
                    }
                }
                reply->deleteLater();
            });
    manager->get(request);
}

void DLLPinCode::setLanguage()
{
    if(languageGlobal == "fi")
    {
        finnish();
    }
    else
    {
        english();
    }
}

bool DLLPinCode::postLogin(QString hex, QString pin)
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

        if(token == "frozen")
        {
            accountFreezed();
            return false;
        }

        if(token == "false")
            return false;

        return true;
    }
    else {
        qDebug() << Q_FUNC_INFO<< "Network error: " << networkReply->errorString();
        return false;
    }
}

void DLLPinCode::enterClickHandler()
{

    timer->stop();
    ui->buttonEnter->setFlat(true);
    ui->buttonEnter->setDisabled(true);
    CheckPin = ui->lineEdit->text();
    QString hex = cardHexCode;
    QString pin = CheckPin;

    if(!postLogin(hex, pin))
    {
        qDebug() << Q_FUNC_INFO << "wrong login info";

        wrongAttempts--;
//      if(wrongAttempts <= 0)
//        {
//            accountFreezed();
//        }
        if(languageGlobal == "fi")
        {
            ui->label->setText("Väärin, syötä tunnusluku uudestaan.");
            ui->labelAttempts->setText(QString::number(wrongAttempts) + " yritys(tä) jäljellä!");
        }
        else
        {
            ui->label->setText("Wrong PIN, please try again again.");
            ui->labelAttempts->setText(QString::number(wrongAttempts) + " attempt(s) left!");
        }

        timer->start(30000);
//        updateWrongAttemptsInCard(cardID,wrongAttempts,token);

        ui->labelAttempts->setVisible(true);
        clearClickHandler();
        emptyLineEdit();
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "correct login info";
//        updateWrongAttemptsInCard(cardID, 3, token);
        getCardIDFromDb();
        while(cardID.isEmpty())
        {
            QApplication::processEvents();
        }
        emit LoginSuccess(cardID.toInt(), token);
        done(Accepted);
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
        emptyLineEdit();
}


void DLLPinCode::clearClickHandler()
{
      InsertingPin = "";
      ui->lineEdit->clear();
      timer->stop();
      timer->start(30000);
      emptyLineEdit();
}

void DLLPinCode::stopClickHandler()
{
        timer->stop();
        emit LoginSuccess(0, token);
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
        QTimer::singleShot(5000, this, &QDialog::reject);

}

void DLLPinCode::accountFreezed()
{

      timer->stop();
      emit LoginSuccess(0, token);
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
      QTimer::singleShot(5000, this, &QDialog::reject);
}

void DLLPinCode::finnish()
{
      ui->label->setText("Näppäile PIN-koodi");
      ui->labelAttempts->setText(" yritys(tä) jäljellä");
      ui->labelFreezed1->setText("Tili jäädytetty liian monen yrityksen takia.");
      ui->labelFreezed2->setText("Ota yhteys asiakaspalvelumme numeroon: +358 10 1234567");
      ui->labelInterrupt->setText("Tapahtuma keskeytetty");
      ui->label_3->setText("ja paina ENTER");
}

void DLLPinCode::english()
{
      ui->label->setText("Enter 4-digit PIN code");
      ui->labelAttempts->setText(" attempt(s) left");
      ui->labelFreezed1->setText("Account frozen due to excessive amount of attempts.");
      ui->labelFreezed2->setText("Please contact our customer service number +358 10 1234567");
      ui->labelInterrupt->setText("Login aborted");
      ui->label_3->setText("and press ENTER");
}

void DLLPinCode::emptyLineEdit()
{
          if (ui->lineEdit->text().isEmpty())
          {
              ui->buttonEnter->setFlat(true);
              ui->buttonEnter->setDisabled(true);
              ui->ButtonClear->setFlat(true);
              ui->ButtonClear->setDisabled(true);
          }
          else
          {
              ui->buttonEnter->setFlat(false);
              ui->buttonEnter->setDisabled(false);
              ui->ButtonClear->setFlat(false);
              ui->ButtonClear->setDisabled(false);
          }
}

void DLLPinCode::sound()
{
          player = new QMediaPlayer;
          audioOutput = new QAudioOutput;
          player->setAudioOutput(audioOutput);

          QString soundFilePath = QCoreApplication::applicationDirPath() + "/../../sounds/pincodeFI.mp3";
          qDebug() << "Sound file path:" << soundFilePath;

          if (QFile::exists(soundFilePath)) {
              player->setSource(QUrl::fromLocalFile(soundFilePath));
              audioOutput->setVolume(0.5);  // set volume to 50%
              player->play();
          } else {
              qDebug() << "Sound file does not exist!";
          }
          audioOutput->setVolume(1);
          player->play();
}

//void DLLPinCode::updateWrongAttemptsInCard(const QString& cardID, int newWrongAttempts, const QString& token)
//{
//    qDebug() << "Updating wrongAttempts in card " << cardID << " to " << newWrongAttempts;
//    QString site_url = DLLPinCode::getBaseUrl() + "/card/" + cardID;
//    QNetworkRequest request((site_url));
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    QByteArray authHeader = QString("Bearer %1").arg(token).toLatin1();
//    request.setRawHeader("Authorization", authHeader);
//    QJsonObject requestBody;
//    requestBody.insert("wrongAttempts", newWrongAttempts);
//    QJsonDocument requestBodyDoc(requestBody);
//    QByteArray requestBodyData = requestBodyDoc.toJson();
//    QNetworkAccessManager *manager = new QNetworkAccessManager();

//    connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {
//        if (reply->error()) {
//            qDebug() << "Failed to update wrongAttempts in card " << cardID << ", remaining attempts: " << reply->errorString();
//        }
//        else {
//            qDebug() << "Updated wrongAttempts to idcard" << cardID << ", remaining attempts: " << wrongAttempts;
//        }
//        reply->deleteLater();
//    });
//    manager->put(request, requestBodyData);
//}
