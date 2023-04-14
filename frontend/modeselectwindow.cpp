#include "modeselectwindow.h"
#include "ui_modeselectwindow.h"

#include <QDebug>

ModeSelectWindow::ModeSelectWindow(QWidget *parent, SessionData *session) :
    QDialog(parent),
    ui(new Ui::ModeSelectWindow)
{
    ui->setupUi(this);

    this->session = session;

    session->resetTimer();

    updateUI();
}

ModeSelectWindow::~ModeSelectWindow()
{
    delete ui;
}

void ModeSelectWindow::updateUI()
{

}

void ModeSelectWindow::on_buttonDebit_clicked()
{
    qDebug() << Q_FUNC_INFO << "Clicked debit";
    emit clickMode("debit"); //send to OptionsWindow
}


void ModeSelectWindow::on_buttonCredit_clicked()
{
    qDebug() << Q_FUNC_INFO << "Clicked credit";
    emit clickMode("credit"); //send to OptionsWindow
}

