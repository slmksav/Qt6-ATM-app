#ifndef RECEIPTWINDOW_H
#define RECEIPTWINDOW_H

#include "sessiondata.h"

#include <QDialog>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class ReceiptWindow;
}

class ReceiptWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiptWindow(QWidget *parent = nullptr, SessionData *session = nullptr);
    ~ReceiptWindow();

public slots:
    void updateUI();

signals:
    void clickReceipt(bool);

private slots:
    void on_buttonYes_clicked();

    void on_buttonNo_clicked();

    void sound();


private:
    Ui::ReceiptWindow *ui;

    SessionData * session;

    QString generateLog(QString name);

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};

#endif // RECEIPTWINDOW_H
