#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include <QWidget>
#include "DLLPinCode_global.h"
#include <QTimer>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QDebug>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QNetworkReply>
#include <QJsonObject>

namespace Ui {
class DLLPinCode;
}

class DLLPINCODE_EXPORT DLLPinCode : public QWidget
{
    Q_OBJECT

public:
    explicit DLLPinCode(QWidget *parent = nullptr, QString cardHexCodeReceived = "", QString language = "fi");
    ~DLLPinCode();
    static QString getBaseUrl();
    QString cardHexCode;
    bool postLogin(QString hex, QString pin);
signals:
    void LoginSuccess(int, QString);
private slots:
//    void updateWrongAttemptsInCard(const QString& cardID, int newWrongAttempts, const QString& token);
    void numberClickHandler();
    void enterClickHandler();
    void clearClickHandler();
    void stopClickHandler();
    void accountFreezed();
    int getCardIDFromDb();
  void getWrongAttempts();
    void setLanguage();
    void emptyLineEdit();
private:
    Ui::DLLPinCode *ui;
    QString InsertingPin;
    QString CheckPin;
    QTimer *timer;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QString token;
    QString cardID;
    QString languageGlobal;
    int wrongAttempts;
    void finnish();
    void english();
    QString soundFilePath;
    void sound();
};

#endif // DLLPINCODE_H
