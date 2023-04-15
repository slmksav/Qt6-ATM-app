#ifndef WITHDRAWWINDOW_H
#define WITHDRAWWINDOW_H

#include "receiptwindow.h"
#include "sessiondata.h"

#include <QDialog>

namespace Ui {
class WithdrawWindow;
}

class WithdrawWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawWindow(QWidget *parent = nullptr, SessionData *session = nullptr);
    ~WithdrawWindow();

signals:
    void clickAmount(int);

public slots:
    void updateUI();
    void freezeUI(bool);

private slots:
    void withdrawButtonClicked(int);
    void withdrawMoney(int);
    void handleResponse(bool);

    void on_buttonLogout_clicked();

    void on_buttonReturn_clicked();

private:
    Ui::WithdrawWindow *ui;

    SessionData * session;

    ReceiptWindow * receiptWindow;

    bool invalidAttempt = false;
};

#endif // WITHDRAWWINDOW_H
