#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "balancewindow.h"
#include "changeaccountwindow.h"
#include "modeselectwindow.h"
#include "sessiondata.h"
#include "transactionswindow.h"
#include "withdrawwindow.h"
#include <QWidget>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr, SessionData *session = nullptr);
    ~OptionsWindow();

signals:
    void changeToAccount(int);

public slots:
    void updateUI();

private slots:
    void on_buttonLogout_clicked();

    void on_buttonWithdraw_clicked();
    void changeWithdrawType(QString);

    void on_buttonBalance_clicked();
    void on_buttonTransactions_clicked();
    void on_buttonChangeAccount_clicked();



private:
    Ui::OptionsWindow *ui;

    SessionData * session;

    ChangeAccountWindow * changeAccountWindow;
    TransactionsWindow * transactionsWindow;
    WithdrawWindow * withdrawWindow;
    BalanceWindow * balanceWindow;

    ModeSelectWindow * modeSelectWindow;
};

#endif // OPTIONSWINDOW_H
