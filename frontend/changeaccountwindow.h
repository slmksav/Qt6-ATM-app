#ifndef CHANGEACCOUNTWINDOW_H
#define CHANGEACCOUNTWINDOW_H

#include "sessiondata.h"

#include <QAbstractButton>
#include <QDialog>

namespace Ui {
class ChangeAccountWindow;
}

class ChangeAccountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeAccountWindow(QWidget *parent = nullptr);
    ~ChangeAccountWindow();

signals:
    void changeToAccount(int);

public slots:
    void putSessionData(SessionData *session);
    void updateUI();

private slots:
    void accountButtonClicked(QAbstractButton *);

    void on_buttonPrevious_clicked();
    void on_buttonNext_clicked();

    void on_buttonLogout_clicked();

private:
    Ui::ChangeAccountWindow *ui;
    int listIndex = 0;

    SessionData * session;
};

#endif // CHANGEACCOUNTWINDOW_H
