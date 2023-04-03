#include "changeaccountwindow.h"
#include "ui_changeaccountwindow.h"

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

void ChangeAccountWindow::updateUI(QList<QString> accountNames)
{
    ui->buttonAccount1->setText(accountNames[0]);
    ui->buttonAccount2->setText(accountNames[1]);
    ui->buttonAccount3->setText(accountNames[2]);
    ui->buttonAccount4->setText(accountNames[3]);
    ui->buttonAccount5->setText(accountNames[4]);
}
