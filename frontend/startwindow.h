#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "sessiondata.h"

#include "optionswindow.h"
#include "dllpincode.h"

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

private slots:
    void on_cardInput_textEdited(const QString &input);

    void logout();

    void openPinCode();
    void printReceipt(bool);
    void hidePinCode();

private:
    Ui::StartWindow *ui;

    OptionsWindow * optionsWindow;

    SessionData * session;
    DLLPinCode * pDLLPinCode;
    void startSession(int);
    void updateUI();
};

#endif // STARTWINDOW_H
