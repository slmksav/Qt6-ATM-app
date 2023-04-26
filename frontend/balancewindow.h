#ifndef BALANCEWINDOW_H
#define BALANCEWINDOW_H

#include "sessiondata.h"

#include <QDialog>

namespace Ui {
class BalanceWindow;
}

class BalanceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BalanceWindow(QWidget *parent = nullptr, SessionData *session = nullptr);
    ~BalanceWindow();

public slots:
    void updateUI();

private slots:
    void on_buttonLogout_clicked();

    void on_buttonReturn_clicked();

private:
    Ui::BalanceWindow *ui;

    SessionData * session;
};

#endif // BALANCEWINDOW_H
