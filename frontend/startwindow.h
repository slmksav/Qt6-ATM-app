#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "sessiondata.h"

#include "optionswindow.h"
#include "dllpincode.h"
#include "balancewindow.h"
#include "changeaccountwindow.h"
#include "transactionswindow.h"
#include "withdrawwindow.h"

#include "modeselectwindow.h"
#include "receiptwindow.h"

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
    //void sendHexa(const QString &hexa);

private slots:
    void on_cardInput_textEdited(const QString &input);

    void logout();

    void openWithdraw();
    void withdrawMoney(int);

    void openModeSelect();
    void changeWithdrawType(QString);

    void openBalance();
    void openTransactions();
    void openChangeAccount();
    void openPinCode();
    void printReceipt(bool);

private:
    Ui::StartWindow *ui;

    OptionsWindow * optionsWindow;

//    ChangeAccountWindow * changeAccountWindow;
//    TransactionsWindow * transactionsWindow;
//    WithdrawWindow * withdrawWindow;
//    BalanceWindow * balanceWindow;

//    ModeSelectWindow * modeSelectWindow;
//    ReceiptWindow * receiptWindow;

    SessionData * session;
    DLLPinCode * pDLLPinCode;
    void startSession(int);
    void updateUI();
};

#endif // STARTWINDOW_H
