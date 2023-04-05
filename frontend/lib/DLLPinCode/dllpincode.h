#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include <QDialog>
#include "DLLPinCode_global.h"
#include <QTimer>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>

namespace Ui {
class DLLPinCode;
}

class DLLPINCODE_EXPORT DLLPinCode : public QDialog
{
    Q_OBJECT

public:
    explicit DLLPinCode(QWidget *parent = nullptr);
    ~DLLPinCode();
    static QString getBaseUrl();
    QString cardhexcodeSQL;
    QString cardHexCode;
signals:
    void sendPin(short);
    void LoginSuccess(bool LoginAttempt);
public slots:
    //tämä funktio vastaanottaa cardhexcoden Mikan DLLpincoden käyttöön (kts. mainwindow.cpp:n signaalit)
    QString handleCardHexCodeReceived(QString hexCode);
private slots:
    void numberClickHandler();
    void enterClickHandler();
    void clearClickHandler();
    void stopClickHandler();
   //void getCardIDBasedOnCardHexCodeFromDb();
    void getCardhexcodeFromDb(const QString& cardId);

private:
    Ui::DLLPinCode *ui;
    QString InsertingPin;
    QString CheckPin;
    QString SQLPin;
    QString InsertedPin;
    bool CompareStrings(QString,QString);
    QTimer *timer;
    QString SQLHexCode;
    QString response_data;
    QString username;
    QString token;
    QString cardID = "2";
};

#endif // DLLPINCODE_H
