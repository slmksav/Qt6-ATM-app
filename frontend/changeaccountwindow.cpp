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

void ChangeAccountWindow::updateUI(/*QList<QString> accountNames*/)
{
    QList<QAbstractButton *> accountButtons = ui->buttonGroup->buttons();
    for (int i = listIndex; i < 5 + listIndex; ++i) {
        qDebug() << "accountNames list size: " << session->additionalAccountNames.count() <<
                    "listIndex: " << listIndex;
        //index would traverse outside of list
        if(i >= session->additionalAccountNames.count())
        {
            qDebug() << "Index outside of list, outputting a blank";
            ui->buttonGroup->button(
                        ui->buttonGroup->id(accountButtons[i])
                        )->setText(" ");
        }
        else
        {
            qDebug() << "Index inside of list, outputting accountNames[" << i;
            ui->buttonGroup->button(
                        ui->buttonGroup->id(accountButtons[i])
                        )->setText(session->additionalAccountNames[i]);
        }
    }
}
