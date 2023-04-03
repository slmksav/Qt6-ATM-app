#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include <QDialog>
#include "DLLPinCode_global.h"

namespace Ui {
class CodeUI;
}

class DLLPINCODE_EXPORT CodeUI : public QDialog
{
    Q_OBJECT

public:
    explicit CodeUI(QWidget *parent = nullptr);
    ~CodeUI();
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
    Ui::CodeUI *ui;
    QString InsertingPin;
    QString CheckPin;
    QString SQLPin;
    QString InsertedPin;
    bool CompareStrings(QString,QString);
};

#endif // DLLPINCODE_H
