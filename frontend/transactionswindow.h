#ifndef TRANSACTIONSWINDOW_H
#define TRANSACTIONSWINDOW_H

#include "sessiondata.h"

#include <QDialog>

namespace Ui {
class TransactionsWindow;
}

class TransactionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QWidget *parent = nullptr);
    ~TransactionsWindow();

public slots:
    void putSessionData(SessionData *session);
    void updateUI();

private:
    Ui::TransactionsWindow *ui;

    SessionData * session;
};

#endif // TRANSACTIONSWINDOW_H
