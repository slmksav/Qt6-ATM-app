#include "modeselectwindow.h"
#include "ui_modeselectwindow.h"

ModeSelectWindow::ModeSelectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeSelectWindow)
{
    ui->setupUi(this);
}

ModeSelectWindow::~ModeSelectWindow()
{
    delete ui;
}
