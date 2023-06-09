#include "optionswindow.h"
#include "ui_optionswindow.h"

OptionsWindow::OptionsWindow(QWidget *parent, SessionData *session) :
    QWidget(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);

    this->session = session;

    session->resetTimer();

    updateUI();
}

OptionsWindow::~OptionsWindow()
{
    delete ui;

    session->resetTimer();
}

void OptionsWindow::updateUI()
{
    //account name and type
    ui->labelAccountName->setText(session->customerName + " - " + session->accountType);

    //additional accounts only contains itself
    if(session->additionalAccountIDs.count() <= 1) {
        qDebug() << Q_FUNC_INFO << "no additionals accounts";
        ui->buttonChangeAccount->hide();
    }

    //other ui elements
    if(session->language == "fi")
    {
        ui->buttonBalance->setText("Saldo");
        ui->buttonChangeAccount->setText("Vaihda tiliä");
        ui->buttonLogout->setText("Kirjaudu ulos");
        ui->buttonTransactions->setText("Tapahtumat");
        ui->buttonWithdraw->setText("Nosto");
        ui->label->setText("Nosta käteistä rahaa");
        ui->label2->setText("Tarkastele tilisi saldoa ja luottoa");
        ui->label3->setText("Selaa tilitapahtumia");
    }
    if(session->language == "en")
    {
        ui->buttonBalance->setText("Balance");
        ui->buttonChangeAccount->setText("Change Account");
        ui->buttonLogout->setText("Log out");
        ui->buttonTransactions->setText("Transactions");
        ui->buttonWithdraw->setText("Withdraw");
        ui->label->setText("Withdraw cash from your account");
        ui->label2->setText("Check your account's thresholds");
        ui->label3->setText("Browse through transactions");
    }
}

void OptionsWindow::on_buttonLogout_clicked()
{
    emit session->sendLogout(this);
}

void OptionsWindow::on_buttonWithdraw_clicked()
{
    withdrawWindow = new WithdrawWindow(this, session);

    if(session->accountType == "dual")
    {
        modeSelectWindow = new ModeSelectWindow(this, session);
        connect(modeSelectWindow, SIGNAL(clickMode(QString)),
                this, SLOT(changeWithdrawType(QString)));

        modeSelectWindow->show();
    }
    else
    {
        withdrawWindow->show();
    }
}

void OptionsWindow::changeWithdrawType(QString mode)
{
    session->withdrawMode = mode;
    qDebug() << Q_FUNC_INFO << "Withdraw mode changed to: " << session->withdrawMode;

    withdrawWindow->updateUI();
    withdrawWindow->show();

    delete modeSelectWindow;
    modeSelectWindow = nullptr;
}


void OptionsWindow::on_buttonBalance_clicked()
{
    balanceWindow = new BalanceWindow(this, session);
    balanceWindow->show();
}


void OptionsWindow::on_buttonTransactions_clicked()
{
    transactionsWindow = new TransactionsWindow(this, session);
    transactionsWindow->show();
}


void OptionsWindow::on_buttonChangeAccount_clicked()
{
    changeAccountWindow = new ChangeAccountWindow(this, session);

    connect(changeAccountWindow, SIGNAL(changeToAccount(int)),
            this, SIGNAL(changeToAccount(int)));

    changeAccountWindow->show();   
}

