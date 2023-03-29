#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QString getBaseUrl();

private slots:
    void loginSlot(QNetworkReply *reply);
    void on_mikaButton_clicked();
    void on_customerButton_clicked();
    void getCustomerData();

private:
    Ui::MainWindow *ui;
    QNetworkReply *reply;
    QNetworkAccessManager *loginManager;
    QString response_data;
    QString username;
    QString token;
};

#endif // MAINWINDOW_H
