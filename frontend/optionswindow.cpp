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

void OptionsWindow::putSessionData(SessionData *session)
{
    this->session = session;
    updateUI();
}

void OptionsWindow::updateUI()
{
    ui->labelAccountName->setText(session->customerName + " - " + session->accountType);
}

void OptionsWindow::on_buttonLogout_clicked()
{

}

void OptionsWindow::on_buttonWithdraw_clicked()
{
    withdrawWindow = new WithdrawWindow(this);

    if(session->accountType == "dual")
    {
        modeSelectWindow = new ModeSelectWindow(this);
        connect(modeSelectWindow, SIGNAL(clickMode(QString)),
                this, SLOT(changeWithdrawType(QString)));

        modeSelectWindow->show();
    }
    else
    {
        withdrawWindow->putSessionData(session);
        withdrawWindow->show();
    }
}

void OptionsWindow::changeWithdrawType(QString mode)
{
    session->withdrawMode = mode;
    qDebug() << "Withdraw mode changed to: " << session->withdrawMode;

    withdrawWindow->putSessionData(session);
    withdrawWindow->show();

    delete modeSelectWindow;
    modeSelectWindow = nullptr;
}


void OptionsWindow::on_buttonBalance_clicked()
{

}


void OptionsWindow::on_buttonTransactions_clicked()
{
    transactionsWindow = new TransactionsWindow(this);
    transactionsWindow->putSessionData(session);
    transactionsWindow->show();
}


void OptionsWindow::on_buttonChangeAccount_clicked()
{
    changeAccountWindow = new ChangeAccountWindow(this);
    changeAccountWindow->putSessionData(session);
    changeAccountWindow->show();
}

