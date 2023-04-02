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
