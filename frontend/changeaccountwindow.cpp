#include "changeaccountwindow.h"
#include "ui_changeaccountwindow.h"
#include <QDebug>

ChangeAccountWindow::ChangeAccountWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeAccountWindow)
{
    ui->setupUi(this);
}

ChangeAccountWindow::~ChangeAccountWindow()
{
    delete ui;
}

void ChangeAccountWindow::putSessionData(SessionData *session)
{
    this->session = session;
    updateUI();
}

void ChangeAccountWindow::updateUI()
{
    //see if previous can be shown
    if(listIndex == 0)
    {
        ui->buttonPrevious->setFlat(true);
        ui->buttonPrevious->setDisabled(true);
    }
    else
    {
        ui->buttonPrevious->setFlat(false);
        ui->buttonPrevious->setDisabled(false);
    }

    //see if next can be shown
    if(session->additionalAccountNames.count() - listIndex <= 5)
    {
        ui->buttonNext->setFlat(true);
        ui->buttonNext->setDisabled(true);
    }
    else
    {
        ui->buttonNext->setFlat(false);
        ui->buttonNext->setDisabled(false);
    }

    //prints the list
    QList<QAbstractButton *> accountButtons = ui->buttonGroup->buttons();
    for (int i = 0; i < 5; ++i) {
        qDebug() << "accountNames list size: " << session->additionalAccountNames.count() <<
                    "listIndex: " << listIndex;
        //index would traverse outside of list
        if(i + listIndex >= session->additionalAccountNames.count())
        {
            qDebug() << "Index outside of list, outputting a blank";
            ui->buttonGroup->button(
                        ui->buttonGroup->id(accountButtons[i])
                        )->setText(" ");
        }
        else
        {
            qDebug() << "Index inside of list, outputting accountNames[" << i + listIndex;
            ui->buttonGroup->button(
                        ui->buttonGroup->id(accountButtons[i])
                        )->setText(session->additionalAccountNames[i + listIndex]);
        }
    }
}

void ChangeAccountWindow::on_buttonPrevious_clicked()
{
    listIndex -= 5;
    updateUI();
}


void ChangeAccountWindow::on_buttonNext_clicked()
{
    listIndex += 5;
    updateUI();
}


void ChangeAccountWindow::on_buttonLogout_clicked()
{
    emit session->sendLogout();
}

