#ifndef WITHDRAWWINDOW_H
#define WITHDRAWWINDOW_H

#include "receiptwindow.h"
#include "sessiondata.h"

#include <QDialog>

namespace Ui {
class WithdrawWindow;
}

class WithdrawWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WithdrawWindow(QWidget *parent = nullptr, SessionData *session = nullptr);
    ~WithdrawWindow();

public slots:
    void updateUI();
    void freezeUI(bool);

private slots:
    void withdrawButtonClicked(int);
    void withdrawMoney(int);
    void handleResponse(bool);

    void on_buttonLogout_clicked();

    void on_buttonReturn_clicked();

    void on_buttonIncrement_clicked();

    void on_buttonDecrement_clicked();

    void on_buttonCustomWithdraw_clicked();

private:
    Ui::WithdrawWindow *ui;

    SessionData * session;

    ReceiptWindow * receiptWindow;

    bool invalidAttempt = false;

    int customWithdrawAmount = 40;
};

#endif // WITHDRAWWINDOW_H
