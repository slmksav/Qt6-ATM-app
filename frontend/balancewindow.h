#ifndef BALANCEWINDOW_H
#define BALANCEWINDOW_H

#include "sessiondata.h"

#include <QDialog>

namespace Ui {
class BalanceWindow;
}

class BalanceWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BalanceWindow(QWidget *parent = nullptr);
    ~BalanceWindow();

public slots:
    void putSessionData(SessionData *session);
    void updateUI();

private slots:
    void on_buttonLogout_clicked();

    void on_buttonReturn_clicked();

private:
    Ui::BalanceWindow *ui;

    SessionData * session;
};

#endif // BALANCEWINDOW_H
