#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include <QDialog>
#include "DLLPinCode_global.h"

namespace Ui {
class DLLPinCode;
}

class DLLPINCODE_EXPORT DLLPinCode : public QDialog
{
    Q_OBJECT

public:
    explicit DLLPinCode(QWidget *parent = nullptr);
    ~DLLPinCode();
signals:
    void sendPin(short);
public slots:
    //tämä funktio vastaanottaa cardhexcoden Mikan DLLpincoden käyttöön (kts. mainwindow.cpp:n signaalit)
    void handleCardHexCodeReceived(const QString& hexCode);
private slots:
    void numberClickHandler();
    void enterClickHandler();
    void clearClickHandler();
    void stopClickHandler();


private:
    Ui::DLLPinCode *ui;
    QString InsertingPin;
    QString CheckPin;
    QString SQLPin;
    QString InsertedPin;
    bool CompareStrings(QString,QString);
};

#endif // DLLPINCODE_H
