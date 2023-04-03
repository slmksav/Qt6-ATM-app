#ifndef MODESELECTWINDOW_H
#define MODESELECTWINDOW_H

#include <QDialog>

namespace Ui {
class ModeSelectWindow;
}

class ModeSelectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModeSelectWindow(QWidget *parent = nullptr);
    ~ModeSelectWindow();

signals:
    void clickMode(QString);

private slots:
    void on_buttonDebit_clicked();
    void on_buttonCredit_clicked();

private:
    Ui::ModeSelectWindow *ui;
};

#endif // MODESELECTWINDOW_H
