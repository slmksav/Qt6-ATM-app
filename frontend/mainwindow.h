#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "dllserialport.h"
#include "dllrestapi.h"
#include "dllpincode.h"
#include "optionswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void handleSerialDataReceived(const QString& data);
    ~MainWindow();
    static QString getBaseUrl();

signals:
    //tämä funktio päivittää nykyisen luetun cardhexcoden
    void leikkiHexaSignaali(QString);

private slots:
    void on_customerButton_clicked();
    void getCustomerData();
    void getCardhexcodeFromDb();
private:
    Ui::MainWindow *ui;
    QNetworkReply *reply;
    DLLSerialPort *m_serialPort;
    DLLPinCode *m_DLLPinCode;
    QNetworkAccessManager *loginManager;
    QString response_data;
    QString username;
    QString token;
    QString cardhexcode;
    QString cardhexcodeSQLTest;

    DLLPinCode * mikanDLL;
};

#endif // MAINWINDOW_H
