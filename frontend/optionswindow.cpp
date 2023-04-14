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

    session->resetTimer();
}

void OptionsWindow::putSessionData(SessionData *session)
{
    this->session = session;

    session->resetTimer();

    updateUI();
}

void OptionsWindow::updateUI()
{
    //account name and type
    ui->labelAccountName->setText(session->customerName + " - " + session->accountType);

    //other ui elements
    if(session->language == "fi")
    {
        ui->buttonBalance->setText("Saldo");
        ui->buttonChangeAccount->setText("Vaihda Tiliä");
        ui->buttonLogout->setText("Kirjaudu Ulos");
        ui->buttonTransactions->setText("Tapahtumat");
        ui->buttonWithdraw->setText("Nosto");
    }
    if(session->language == "en")
    {
        ui->buttonBalance->setText("Balance");
        ui->buttonChangeAccount->setText("Change Account");
        ui->buttonLogout->setText("Logout");
        ui->buttonTransactions->setText("Transactions");
        ui->buttonWithdraw->setText("Withdraw");
    }
}

void OptionsWindow::on_buttonLogout_clicked()
{
    emit session->sendLogout();
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
    qDebug() << Q_FUNC_INFO << "Withdraw mode changed to: " << session->withdrawMode;

    withdrawWindow->putSessionData(session);
    withdrawWindow->show();

    delete modeSelectWindow;
    modeSelectWindow = nullptr;
}


void OptionsWindow::on_buttonBalance_clicked()
{
    balanceWindow = new BalanceWindow(this);
    balanceWindow->putSessionData(session);
    balanceWindow->show();
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

    connect(changeAccountWindow, SIGNAL(changeToAccount(int)),
            this, SIGNAL(changeToAccount(int)));

    changeAccountWindow->putSessionData(session);
    changeAccountWindow->show();   
}

