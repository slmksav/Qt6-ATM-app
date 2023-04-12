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
    explicit DLLPinCode(QWidget *parent = nullptr, QString cardHexCodeReceived = "");
    ~DLLPinCode();
    static QString getBaseUrl();
    QString cardhexcodeSQL;
    QString cardHexCode;
signals:
    void LoginSuccess(int);
private slots:
    void updateWrongAttemptsInCard(const QString& cardID, int newWrongAttempts, const QString& token);
    void numberClickHandler();
    void enterClickHandler();
    void clearClickHandler();
    void stopClickHandler();
    void accountFreezed();
    void getCardIDFromDb();
    void getCardInfoFromDb();
private:
    Ui::DLLPinCode *ui;
    QString InsertingPin;
    QString CheckPin;
    QString SQLPin;
    QTimer *timer;
    QString token;
    QString cardID;
    int wrongAttempts; 
};

#endif // DLLPINCODE_H
