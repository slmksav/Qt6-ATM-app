#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "sessiondata.h"

#include "optionswindow.h"
#include "dllpincode.h"
#include "dllrestapi.h"
#include "dllserialport.h"

#include <QMainWindow>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

signals:
    void testOhitaKorttiSignal(QString);
    void testOhitaPINSignal(int);

private slots:
    void languageButtonClicked(int);

    void logout();
    void printReceipt(bool); //this might be redundant

    void openDLLPinCode(QString);

    void startSession(int);
    void fetchDataWithDLL(int);
    void swapToAccount(int);

    void on_buttonOhitaKortti_clicked(); //this shall be removed on release
    void on_buttonOhitaPIN_clicked(); //this shall be removed on release

private:
    Ui::StartWindow *ui;

    OptionsWindow * optionsWindow;

    SessionData * session;

    DLLPinCode * pDLLPinCode;
    DLLRestApi * pDLLRestApi;
    DLLSerialPort * pDLLSerialPort;

    QString language = "fi";

    void updateUI();
};

#endif // STARTWINDOW_H
