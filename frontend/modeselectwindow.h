#ifndef MODESELECTWINDOW_H
#define MODESELECTWINDOW_H

#include "sessiondata.h"

#include <QDialog>

namespace Ui {
class ModeSelectWindow;
}

class ModeSelectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModeSelectWindow(QWidget *parent = nullptr, SessionData *session = nullptr);
    ~ModeSelectWindow();

signals:
    void clickMode(QString);

public slots:
    void updateUI();

private slots:
    void on_buttonDebit_clicked();
    void on_buttonCredit_clicked();

private:
    Ui::ModeSelectWindow *ui;

    SessionData * session;
};

#endif // MODESELECTWINDOW_H
