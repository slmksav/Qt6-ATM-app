#ifndef TRANSACTIONSWINDOW_H
#define TRANSACTIONSWINDOW_H

#include "sessiondata.h"

#include <QDialog>

namespace Ui {
class TransactionsWindow;
}

class TransactionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QWidget *parent = nullptr, SessionData *session = nullptr);
    ~TransactionsWindow();

public slots:
    void updateUI();

private slots:
    void on_buttonLogout_clicked();

    void on_buttonReturn_clicked();

    void on_buttonPrevious_clicked();

    void on_buttonNext_clicked();

private:
    Ui::TransactionsWindow *ui;

    int listIndex = 0;

    SessionData * session;
};

#endif // TRANSACTIONSWINDOW_H
