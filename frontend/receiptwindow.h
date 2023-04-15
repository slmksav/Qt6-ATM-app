#ifndef RECEIPTWINDOW_H
#define RECEIPTWINDOW_H

#include "sessiondata.h"

#include <QDialog>

namespace Ui {
class ReceiptWindow;
}

class ReceiptWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiptWindow(QWidget *parent = nullptr, SessionData *session = nullptr);
    ~ReceiptWindow();

public slots:
    void updateUI();

signals:
    void clickReceipt(bool);

private slots:
    void on_buttonYes_clicked();

    void on_buttonNo_clicked();

private:
    Ui::ReceiptWindow *ui;

    SessionData * session;
};

#endif // RECEIPTWINDOW_H
