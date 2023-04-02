#include "optionswindow.h"
#include "ui_optionswindow.h"

OptionsWindow::OptionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::updateUI(QString customerName, QString accountType)
{

}

void OptionsWindow::on_buttonLogout_clicked()
{

}

void OptionsWindow::on_buttonWithdraw_clicked()
{
    emit clickWithdraw();
//    withdrawWindow = new WithdrawWindow(this);

//    if(1/*mode == "dual"*/)
//    {
//        modeSelectWindow = new ModeSelectWindow(this);
//    }

//    withdrawWindow->open();
}


void OptionsWindow::on_buttonBalance_clicked()
{
//    balanceWindow = new BalanceWindow(this);
//    balanceWindow->open();
}


void OptionsWindow::on_buttonTransactions_clicked()
{
//    transactionsWindow = new TransactionsWindow(this);
//    transactionsWindow->open();
}


void OptionsWindow::on_buttonChangeAccount_clicked()
{
//    changeAccountWindow = new ChangeAccountWindow(this);
//    changeAccountWindow->open();
}

