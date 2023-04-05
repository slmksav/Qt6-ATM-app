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
    void LoginSuccess(int);
public slots:
    //tämä funktio vastaanottaa cardhexcoden Mikan DLLpincoden käyttöön (kts. mainwindow.cpp:n signaalit)
    QString handleCardHexCodeReceived(QString hexCode);
private slots:
    void numberClickHandler();
    void enterClickHandler();
    void clearClickHandler();
    void stopClickHandler();
    void accountFreezed();
   //void getCardIDBasedOnCardHexCodeFromDb();
    void getCardInfoFromDb(const QString& cardId);

private:
    Ui::DLLPinCode *ui;
    QString InsertingPin;
    QString CheckPin;
    QString SQLPin;
    QTimer *timer;
    QString token;
    QString cardID = "2";
    int wrongAttempts;
};

#endif // DLLPINCODE_H
