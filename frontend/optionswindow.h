#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QDialog>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();

signals:
    void clickLogout();

    void clickWithdraw();
    void clickBalance();
    void clickTransactions();
    void clickChangeAccount();

public slots:
    void updateUI(QString, QString);

private slots:
    void on_buttonLogout_clicked();
    void on_buttonWithdraw_clicked();
    void on_buttonBalance_clicked();
    void on_buttonTransactions_clicked();
    void on_buttonChangeAccount_clicked();

private:
    Ui::OptionsWindow *ui;


};

#endif // OPTIONSWINDOW_H
