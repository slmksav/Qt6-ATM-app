#include "withdrawwindow.h"
#include "ui_withdrawwindow.h"

#include <QDebug>

WithdrawWindow::WithdrawWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WithdrawWindow)
{
    ui->setupUi(this);

    connect(ui->buttonGroup, SIGNAL(idClicked(int)),
            this, SLOT(withdrawButtonClicked(int)));
}

WithdrawWindow::~WithdrawWindow()
{
    delete ui;
}

void WithdrawWindow::withdrawExceedWarning(QString mode)
{
    if(mode == "debit")
    {
        ui->labelWithdrawWarning->setText("Kate ei riitä!");
    }
    else
    {
        ui->labelWithdrawWarning->setText("Luotto ei riitä!");
    }
}

void WithdrawWindow::updateUI(QString)
{

}

void WithdrawWindow::withdrawButtonClicked(int buttonID)
{
    //get button value (text of the button)
    int buttonValue = ui->buttonGroup->button(buttonID)->text().toInt();

    qDebug() << "Withdrawal amount selected: " << buttonValue;
    emit clickAmount(buttonValue);
}

